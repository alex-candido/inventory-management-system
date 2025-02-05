#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"

#define STOCK_FILE "data/stock.csv"

void create_stock(int product_id, int quantity, const char *location)
{
  FILE *file = fopen(STOCK_FILE, "a");
  if (file == NULL)
  {
    printf("Failed to open stock file.\n");
    return;
  }
  fprintf(file, "%d,%d,%s\n", product_id, quantity, location);
  fclose(file);
  printf("Stock created successfully.\n");
}

void read_stock(int product_id)
{
  FILE *file = fopen(STOCK_FILE, "r");
  if (file == NULL)
  {
    printf("Failed to open stock file.\n");
    return;
  }
  char line[255];
  printf("Product ID, Quantity, Location\n");
  while (fgets(line, sizeof(line), file))
  {
    int id, quantity;
    char location[255];
    sscanf(line, "%d,%d,%s", &id, &quantity, location);
    if (id == product_id)
    {
      printf("%d, %d, %s\n", id, quantity, location);
    }
  }
  fclose(file);
}

void update_stock(int product_id, int quantity, const char *location)
{
  FILE *file = fopen(STOCK_FILE, "r+");
  if (file == NULL)
  {
    printf("Failed to open stock file.\n");
    return;
  }

  char line[255];
  long pos;
  int found = 0;
  while (fgets(line, sizeof(line), file))
  {
    pos = ftell(file);
    int id;
    sscanf(line, "%d", &id);
    if (id == product_id)
    {
      fseek(file, pos - strlen(line), SEEK_SET);
      fprintf(file, "%d,%d,%s\n", product_id, quantity, location);
      found = 1;
      break;
    }
  }
  fclose(file);

  if (found)
  {
    printf("Stock updated successfully.\n");
  }
  else
  {
    printf("Stock not found.\n");
  }
}

void delete_stock(int product_id)
{
  FILE *file = fopen(STOCK_FILE, "r");
  if (file == NULL)
  {
    printf("Failed to open stock file.\n");
    return;
  }

  FILE *temp_file = fopen("data/temp_stock.csv", "w");
  if (temp_file == NULL)
  {
    printf("Failed to create temporary file.\n");
    fclose(file);
    return;
  }

  char line[255];
  int found = 0;
  while (fgets(line, sizeof(line), file))
  {
    int id;
    sscanf(line, "%d", &id);
    if (id != product_id)
    {
      fputs(line, temp_file);
    }
    else
    {
      found = 1;
    }
  }

  fclose(file);
  fclose(temp_file);

  if (found)
  {
    remove(STOCK_FILE);
    rename("data/temp_stock.csv", STOCK_FILE);
    printf("Stock deleted successfully.\n");
  }
  else
  {
    printf("Stock not found.\n");
  }
}
