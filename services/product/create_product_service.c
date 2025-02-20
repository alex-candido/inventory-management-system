#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "services/product/create_product_service.h"

#define PRODUCT_FILE "data/products.csv"

void create_product(const char *name, const char *category, double price)
{
  FILE *file = fopen(PRODUCT_FILE, "a");
  if (file == NULL)
  {
    printf("Failed to open product file.\n");
    return;
  }
  int id = rand() % 1000; // Gerar um id aleatório para o produto
  fprintf(file, "%d,%s,%s,%.2f\n", id, name, category, price);
  fclose(file);
  printf("Product created successfully.\n");
}
