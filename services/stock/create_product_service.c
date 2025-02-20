#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/services/stock/create_stock_service.h"

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
