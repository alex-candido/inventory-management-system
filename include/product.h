#ifndef PRODUCT_H
#define PRODUCT_H

#include <gtk/gtk.h>

// Product structure definition
typedef struct
{
  int id;
  char name[100];
  char description[500];
  double price;
  int quantity;
  char category[50];
  char *created_at;
  char *updated_at;
} Product;

// Product service functions
void init_products(void);
void product_add(Product *product);
void product_update(Product *product);
void product_delete(int id);

Product *product_get_by_id(int id);
GList *product_get_all(void);
GList *product_search(const char *query);

// File operations
gboolean product_save_to_file(GList *products);
GList *product_load_from_file(void);

#endif /* PRODUCT_H */
