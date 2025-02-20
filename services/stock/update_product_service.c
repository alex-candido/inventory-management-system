#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "services/stock/update_stock_service.h"

#define STOCK_FILE "data/stock.csv"

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
