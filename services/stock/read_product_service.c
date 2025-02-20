#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/services/stock/read_stock_service.h"

#define STOCK_FILE "data/stock.csv"

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
