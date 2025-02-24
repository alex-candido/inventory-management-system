#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include "utils.h"
#include "product.h"
#include "stock.h"

#define MAX_LINE_LENGTH 1024
#define PRODUCT_SEED_FILE "data/seeds/products.csv"
#define STOCK_SEED_FILE "data/seeds/stocks.csv"

void ensure_seed_directory(void)
{
  struct stat st = {0};
  if (stat("data/seeds", &st) == -1)
  {
    mkdir("data/seeds", 0777);
  }
}

char *trim(char *str)
{
  char *end;

  while (isspace((unsigned char)*str))
    str++;

  if (*str == 0)
    return str;

  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;

  end[1] = '\0';

  return str;
}

void seed_products(void)
{
  ensure_seed_directory();
  FILE *file = fopen(PRODUCT_SEED_FILE, "r");
  if (!file)
  {
    printf("Error: Could not open product seed file %s\n", PRODUCT_SEED_FILE);
    return;
  }

  char line[MAX_LINE_LENGTH];
  int line_number = 0;

  while (fgets(line, sizeof(line), file))
  {
    line_number++;
    if (line_number == 1)
      continue; // Skip header line

    // Remove newline character
    line[strcspn(line, "\n")] = 0;

    // Parse CSV line
    Product product = {0};
    char *token;
    int field = 0;

    token = strtok(line, ",");
    while (token != NULL && field < 5)
    {
      token = trim(token);
      switch (field)
      {
      case 0: // name
        strncpy(product.name, token, sizeof(product.name) - 1);
        break;
      case 1: // description
        strncpy(product.description, token, sizeof(product.description) - 1);
        break;
      case 2: // price
        product.price = atof(token);
        break;
      case 3: // quantity
        product.quantity = atoi(token);
        break;
      case 4: // category
        strncpy(product.category, token, sizeof(product.category) - 1);
        break;
      }
      token = strtok(NULL, ",");
      field++;
    }

    if (field == 5)
    {
      product_add(&product);
      printf("Added product: %s\n", product.name);
    }
    else
    {
      printf("Warning: Invalid product data at line %d\n", line_number);
    }
  }

  fclose(file);
}

void seed_stocks(void)
{
  ensure_seed_directory();
  FILE *file = fopen(STOCK_SEED_FILE, "r");
  if (!file)
  {
    printf("Error: Could not open stock seed file %s\n", STOCK_SEED_FILE);
    return;
  }

  char line[MAX_LINE_LENGTH];
  int line_number = 0;

  while (fgets(line, sizeof(line), file))
  {
    line_number++;
    if (line_number == 1)
      continue; // Skip header line

    // Remove newline character
    line[strcspn(line, "\n")] = 0;

    // Parse CSV line
    Stock stock = {0};
    char *token;
    int field = 0;

    token = strtok(line, ",");
    while (token != NULL && field < 3)
    {
      token = trim(token);
      switch (field)
      {
      case 0: // product_id
        stock.product_id = atoi(token);
        break;
      case 1: // quantity
        stock.quantity = atoi(token);
        break;
      case 2: // location
        strncpy(stock.location, token, sizeof(stock.location) - 1);
        break;
      }
      token = strtok(NULL, ",");
      field++;
    }

    if (field == 3)
    {
      stock_add(&stock);
      printf("Added stock for product ID: %d\n", stock.product_id);
    }
    else
    {
      printf("Warning: Invalid stock data at line %d\n", line_number);
    }
  }

  fclose(file);
}
