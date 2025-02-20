#ifndef PRODUCT_READ_PRODUCT_SERVICE_H
#define PRODUCT_READ_PRODUCT_SERVICE_H

#include <gtk/gtk.h>

#define MAX_STRING_LENGTH 255

typedef struct
{
  int id;
  char name[MAX_STRING_LENGTH];
  char category[MAX_STRING_LENGTH]; // Adicionado o campo category
  char description[MAX_STRING_LENGTH];
  double price;
  int quantity;
  int status;          // 0 = Inativo, 1 = Ativo
  char created_at[20]; // Formato: YYYY-MM-DD HH:MM:SS
  char updated_at[20]; // Formato: YYYY-MM-DD HH:MM:SS
} Product;

int get_total_products();

Product *read_products(int page, int *num_products); // Corrigido para retornar Product*

#endif // PRODUCT_READ_PRODUCT_SERVICE_H
