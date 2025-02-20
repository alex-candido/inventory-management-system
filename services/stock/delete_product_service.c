#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/services/stock/delete_stock_service.h"

#define STOCK_FILE "data/stock.csv"

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
