#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

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

void read_products()
{
  FILE *file = fopen(PRODUCT_FILE, "r");
  if (file == NULL)
  {
    printf("Failed to open product file.\n");
    return;
  }
  char line[255];
  printf("ID, Name, Category, Price\n");
  while (fgets(line, sizeof(line), file))
  {
    printf("%s", line);
  }
  fclose(file);
}

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
