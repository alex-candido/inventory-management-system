#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "services/product/update_product_service.h"

#define PRODUCT_FILE "data/products.csv"

void update_product(int id, const char *name, const char *category, double price)
{
  FILE *file = fopen(PRODUCT_FILE, "r+");
  if (file == NULL)
  {
    printf("Failed to open product file.\n");
    return;
  }

  char line[255];
  long pos;
  int found = 0;
  while (fgets(line, sizeof(line), file))
  {
    pos = ftell(file);
    int product_id;
    sscanf(line, "%d", &product_id);
    if (product_id == id)
    {
      fseek(file, pos - strlen(line), SEEK_SET);
      fprintf(file, "%d,%s,%s,%.2f\n", id, name, category, price);
      found = 1;
      break;
    }
  }
  fclose(file);

  if (found)
  {
    printf("Product updated successfully.\n");
  }
  else
  {
    printf("Product not found.\n");
  }
}
