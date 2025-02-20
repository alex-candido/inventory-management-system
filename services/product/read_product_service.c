#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "services/product/read_product_service.h"

#define PRODUCT_FILE "data/products.csv"
#define PRODUCTS_PER_PAGE 12 // Número de produtos por página

// Função para ler os produtos e retornar o número total de produtos
int get_total_products()
{
  FILE *file = fopen(PRODUCT_FILE, "r");
  if (file == NULL)
  {
    printf("Failed to open product file.\n");
    return -1;
  }

  int count = 0;
  char line[255];
  while (fgets(line, sizeof(line), file))
  {
    count++;
  }

  fclose(file);
  return count;
}

// Função para ler os produtos de uma página específica
Product *read_products(int page, int *num_products)
{
  FILE *file = fopen(PRODUCT_FILE, "r");
  if (file == NULL)
  {
    printf("Failed to open product file.\n");
    return NULL;
  }

  // Calcula o índice do produto inicial e o final a ser exibido na página
  int start_index = (page - 1) * PRODUCTS_PER_PAGE;
  int end_index = start_index + PRODUCTS_PER_PAGE;

  // Contar o total de produtos
  int total_products = get_total_products();
  if (start_index >= total_products)
  {
    fclose(file);
    *num_products = 0;
    return NULL; // Nenhum produto na página
  }

  // Aloca memória para os produtos a serem exibidos na página
  Product *products = malloc(sizeof(Product) * PRODUCTS_PER_PAGE);
  if (products == NULL)
  {
    printf("Memory allocation failed.\n");
    fclose(file);
    return NULL;
  }

  // Leitura do arquivo e preenchimento dos produtos
  int i = 0;
  char line[255];
  int current_index = 0;

  // Pular para o produto inicial da página
  while (fgets(line, sizeof(line), file) && current_index < start_index)
  {
    current_index++;
  }

  // Agora, preenche os produtos da página
  while (fgets(line, sizeof(line), file) && i < PRODUCTS_PER_PAGE && current_index < end_index)
  {
    char *token = strtok(line, ",");
    if (token)
      products[i].id = atoi(token); // Popula o campo id

    token = strtok(NULL, ",");
    if (token)
      strncpy(products[i].name, token, MAX_STRING_LENGTH);

    token = strtok(NULL, ",");
    if (token)
      strncpy(products[i].category, token, MAX_STRING_LENGTH);

    token = strtok(NULL, ",");
    if (token)
      strncpy(products[i].description, token, MAX_STRING_LENGTH);

    token = strtok(NULL, ",");
    if (token)
      products[i].price = strtod(token, NULL); // Usando strtod para converter para double

    token = strtok(NULL, ",");
    if (token)
      products[i].quantity = atoi(token); // Converte para int

    token = strtok(NULL, ",");
    if (token)
      products[i].status = atoi(token); // Converte para int, 0 ou 1

    token = strtok(NULL, ",");
    if (token)
    {
      // Remover espaços extras que possam estar na data
      token = strtok(token, " \n");
      strncpy(products[i].created_at, token, 20);
    }

    token = strtok(NULL, ",");
    if (token)
    {
      // Remover espaços extras que possam estar na data
      token = strtok(token, " \n");
      strncpy(products[i].updated_at, token, 20);
    }

    i++;
    current_index++;
  }

  fclose(file);
  *num_products = i; // Número de produtos lidos para a página
  return products;
}
