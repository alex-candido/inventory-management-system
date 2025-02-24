#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include "product.h"
#include "utils.h"

static GList *product_list = NULL;
static int next_id = 1;

#define DATA_FILE "data/products.dat"

void init_products(void)
{
  product_list = product_load_from_file();
  if (!product_list)
  {
    product_list = NULL;
    next_id = 1;
  }
}

void product_add(Product *product)
{
  Product *new_product = malloc(sizeof(Product));
  if (new_product == NULL)
    return;

  memset(new_product, 0, sizeof(Product));

  new_product->id = next_id++;
  new_product->price = product->price;
  new_product->quantity = product->quantity;

  // Copy strings with proper null termination and size checking
  snprintf(new_product->name, sizeof(new_product->name), "%s", product->name);
  snprintf(new_product->description, sizeof(new_product->description), "%s", product->description);
  snprintf(new_product->category, sizeof(new_product->category), "%s", product->category);

  time_t now = time(NULL);
  char time_str[20];
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));

  new_product->created_at = strdup(time_str);
  new_product->updated_at = strdup(time_str);

  if (!validate_utf8_string(new_product->name) ||
      !validate_utf8_string(new_product->description) ||
      !validate_utf8_string(new_product->category))
  {
    free(new_product->created_at);
    free(new_product->updated_at);
    free(new_product);
    return;
  }

  product_list = g_list_append(product_list, new_product);

  if (!product_save_to_file(product_list))
  {
    product_list = g_list_remove(product_list, new_product);
    free(new_product->created_at);
    free(new_product->updated_at);
    free(new_product);
  }
}

void product_update(Product *product)
{
  if (!product || !validate_utf8_string(product->name) ||
      !validate_utf8_string(product->description) ||
      !validate_utf8_string(product->category))
  {
    return;
  }

  GList *item = product_list;
  while (item)
  {
    Product *current = item->data;
    if (current->id == product->id)
    {
      // Create a backup of the current state
      Product backup = *current;

      // Update fields
      current->price = product->price;
      current->quantity = product->quantity;

      // Safely copy strings with proper null termination
      strncpy(current->name, product->name, sizeof(current->name) - 1);
      current->name[sizeof(current->name) - 1] = '\0';

      strncpy(current->description, product->description, sizeof(current->description) - 1);
      current->description[sizeof(current->description) - 1] = '\0';

      strncpy(current->category, product->category, sizeof(current->category) - 1);
      current->category[sizeof(current->category) - 1] = '\0';

      // Update timestamps
      if (product->created_at)
      {
        free(current->created_at);
        current->created_at = strdup(product->created_at);
      }

      if (!product->updated_at)
      {
        time_t now = time(NULL);
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));
        free(current->updated_at);
        current->updated_at = strdup(time_str);
      }

      if (!product_save_to_file(product_list))
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

void product_delete(int id)
{
  GList *item = product_list;
  while (item)
  {
    Product *product = item->data;
    if (product->id == id)
    {
      GList *temp_list = g_list_copy(product_list);
      temp_list = g_list_remove(temp_list, product);

      if (!product_save_to_file(temp_list))
      {
        g_list_free(temp_list);
        return;
      }

      product_list = g_list_remove(product_list, product);
      free(product->created_at);
      free(product->updated_at);
      free(product);
      g_list_free(temp_list);
      return;
    }
    item = item->next;
  }
}

Product *product_get_by_id(int id)
{
  GList *item = product_list;
  while (item)
  {
    Product *product = item->data;
    if (product->id == id)
    {
      return product;
    }
    item = item->next;
  }
  return NULL;
}

GList *product_get_all(void)
{
  return product_list;
}

GList *product_search(const char *query)
{
  if (!query || strlen(query) == 0)
  {
    return product_get_all();
  }

  GList *results = NULL;
  GList *item = product_list;

  while (item)
  {
    Product *product = item->data;
    char *name_lower = strdup(product->name);
    if (!name_lower)
      continue;

    for (char *p = name_lower; *p; p++)
    {
      *p = tolower(*p);
    }

    if (strstr(name_lower, query) != NULL)
    {
      results = g_list_append(results, product);
    }

    free(name_lower);
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

gboolean product_save_to_file(GList *products)
{
  ensure_data_directory();
  FILE *file = fopen(DATA_FILE, "wb");
  if (!file)
    return FALSE;

  GList *item = products;
  while (item)
  {
    Product *product = item->data;

    // Validar apenas a string necessária, como em stock_save_to_file
    if (!validate_utf8_string(product->name) ||
        !validate_utf8_string(product->description) ||
        !validate_utf8_string(product->category))
    {
      fclose(file);
      return FALSE;
    }

    if (fwrite(product, sizeof(Product), 1, file) != 1)
    {
      fclose(file);
      return FALSE;
    }

    item = item->next;
  }

  fclose(file);
  return TRUE;
}

GList *product_load_from_file(void)
{
  FILE *file = fopen(DATA_FILE, "rb");
  if (!file)
    return NULL;

  GList *loaded_products = NULL;
  Product *product;

  while (1)
  {
    product = malloc(sizeof(Product));
    if (!product)
    {
      fclose(file);
      return loaded_products;
    }

    memset(product, 0, sizeof(Product));

    if (fread(product, sizeof(Product), 1, file) != 1)
    {
      free(product);
      break;
    }

    // Ensure timestamps are properly initialized
    product->created_at = NULL;
    product->updated_at = NULL;

    // Set default timestamps if needed
    time_t now = time(NULL);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));

    product->created_at = strdup(time_str);
    if (!product->created_at)
    {
      free(product);
      continue;
    }

    product->updated_at = strdup(time_str);
    if (!product->updated_at)
    {
      free(product->created_at);
      free(product);
      continue;
    }

    loaded_products = g_list_append(loaded_products, product);

    if (product->id >= next_id)
    {
      next_id = product->id + 1;
    }
  }

  fclose(file);
  return loaded_products;
}
