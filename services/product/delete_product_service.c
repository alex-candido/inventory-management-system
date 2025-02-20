#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "services/product/delete_product_service.h"

#define PRODUCT_FILE "data/products.csv"

void delete_product(int id)
{
  FILE *file = fopen(PRODUCT_FILE, "r");
  if (file == NULL)
  {
    printf("Failed to open product file.\n");
    return;
  }

  FILE *temp_file = fopen("data/temp.csv", "w");
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
    int product_id;
    sscanf(line, "%d", &product_id);
    if (product_id != id)
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
    remove(PRODUCT_FILE);
    rename("data/temp.csv", PRODUCT_FILE);
    printf("Product deleted successfully.\n");
  }
  else
  {
    printf("Product not found.\n");
  }
}
