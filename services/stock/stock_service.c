#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include "stock.h"
#include "utils.h"

static GList *stock_list = NULL;
static int next_id = 1;

#define STOCK_DATA_FILE "data/stocks.dat"

void init_stock(void)
{
  stock_list = stock_load_from_file();
  if (!stock_list)
  {
    stock_list = NULL;
    next_id = 1;
  }
}

void stock_add(Stock *stock)
{
  Stock *new_stock = malloc(sizeof(Stock));
  if (new_stock == NULL)
    return;

  memset(new_stock, 0, sizeof(Stock));

  new_stock->id = next_id++;
  new_stock->product_id = stock->product_id;
  new_stock->quantity = stock->quantity;

  snprintf(new_stock->location, sizeof(new_stock->location), "%s", stock->location);

  time_t now = time(NULL);
  char time_str[20];
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));

  new_stock->created_at = strdup(time_str);
  new_stock->updated_at = strdup(time_str);

  // Validar antes de salvar
  if (!validate_utf8_string(new_stock->location))
  {
    free(new_stock->created_at);
    free(new_stock->updated_at);
    free(new_stock);
    return;
  }

  stock_list = g_list_append(stock_list, new_stock);

  if (!stock_save_to_file(stock_list))
  {
    stock_list = g_list_remove(stock_list, new_stock);
    free(new_stock->created_at);
    free(new_stock->updated_at);
    free(new_stock);
  }
}

void stock_update(Stock *stock)
{
  if (!stock || !validate_utf8_string(stock->location))
  {
    return;
  }

  GList *item = stock_list;
  while (item)
  {
    Stock *current = item->data;
    if (current->id == stock->id)
    {
      // Create a backup of the current state
      Stock backup = *current;

      // Update fields
      current->product_id = stock->product_id;
      current->quantity = stock->quantity;

      strncpy(current->location, stock->location, sizeof(current->location) - 1);
      current->location[sizeof(current->location) - 1] = '\0';

      // Update 'created_at' and 'updated_at'
      if (stock->created_at)
      {
        free(current->created_at);                       // Free old 'created_at' if it's being updated
        current->created_at = strdup(stock->created_at); // Copy new 'created_at'
      }

      // Update 'updated_at' with the current timestamp if not explicitly set
      if (!stock->updated_at)
      {
        time_t now = time(NULL);
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));
        free(current->updated_at);
        current->updated_at = strdup(time_str);
      }

      if (!stock_save_to_file(stock_list))
      {
        // Free the current timestamps before restoring backup
        free(current->created_at);
        free(current->updated_at);

        // Restore the backup
        *current = backup; // Restore all fields at once

        // Re-allocate timestamps since they were freed
        current->created_at = strdup(backup.created_at);
        current->updated_at = strdup(backup.updated_at);
        return;
      }
      return;
    }
    item = item->next;
  }
}

void stock_delete(int id)
{
  GList *item = stock_list;
  while (item)
  {
    Stock *stock = item->data;
    if (stock->id == id)
    {
      GList *temp_list = g_list_copy(stock_list);
      temp_list = g_list_remove(temp_list, stock);

      if (!stock_save_to_file(temp_list))
      {
        g_list_free(temp_list);
        return;
      }

      stock_list = g_list_remove(stock_list, stock);
      free(stock);
      g_list_free(temp_list);
      return;
    }
    item = item->next;
  }
}

Stock *stock_get_by_id(int id)
{
  GList *item = stock_list;
  while (item)
  {
    Stock *stock = item->data;
    if (stock->id == id)
    {
      return stock;
    }
    item = item->next;
  }
  return NULL;
}

GList *stock_get_all(void)
{
  return stock_list;
}

GList *stock_search(const char *query)
{
  if (!query || strlen(query) == 0)
  {
    return stock_get_all();
  }

  GList *results = NULL;
  GList *item = stock_list;

  while (item)
  {
    Stock *stock = item->data;
    char location_lower[100];

    strncpy(location_lower, stock->location, sizeof(location_lower) - 1);
    location_lower[sizeof(location_lower) - 1] = '\0';

    for (char *p = location_lower; *p; p++)
    {
      *p = tolower(*p);
    }

    if (strstr(location_lower, query) != NULL)
    {
      results = g_list_append(results, stock);
    }

    item = item->next;
  }

  return results;
}

static void ensure_data_directory()
{
  struct stat st = {0};
  if (stat("data", &st) == -1)
  {
    mkdir("data", 0777);
  }
}

gboolean stock_save_to_file(GList *stocks)
{
  ensure_data_directory();
  FILE *file = fopen(STOCK_DATA_FILE, "wb");
  if (!file)
    return FALSE;

  GList *item = stocks;
  while (item)
  {
    Stock *stock = item->data;

    // Validate UTF-8 strings before saving
    if (!validate_utf8_string(stock->location))
    {
      fclose(file);
      return FALSE;
    }

    if (fwrite(stock, sizeof(Stock), 1, file) != 1)
    {
      fclose(file);
      return FALSE;
    }
    item = item->next;
  }

  fclose(file);
  return TRUE;
}

GList *stock_load_from_file(void)
{
  FILE *file = fopen(STOCK_DATA_FILE, "rb");
  if (!file)
    return NULL;

  GList *loaded_stocks = NULL;
  Stock *stock;

  while (1)
  {
    stock = malloc(sizeof(Stock));
    if (!stock)
    {
      fclose(file);
      return loaded_stocks;
    }

    memset(stock, 0, sizeof(Stock));

    if (fread(stock, sizeof(Stock), 1, file) != 1)
    {
      free(stock);
      break;
    }

    // Ensure timestamps are properly initialized
    stock->created_at = NULL;
    stock->updated_at = NULL;

    // Set default timestamps if needed
    time_t now = time(NULL);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));

    stock->created_at = strdup(time_str);
    if (!stock->created_at)
    {
      free(stock);
      continue;
    }

    stock->updated_at = strdup(time_str);
    if (!stock->updated_at)
    {
      free(stock->created_at);
      free(stock);
      continue;
    }

    loaded_stocks = g_list_append(loaded_stocks, stock);

    if (stock->id >= next_id)
    {
      next_id = stock->id + 1;
    }
  }

  fclose(file);
  return loaded_stocks;
}
