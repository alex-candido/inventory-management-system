#ifndef STOCK_H
#define STOCK_H

#include <gtk/gtk.h>

// Stock item structure
typedef struct
{
  int id;
  int product_id;
  int quantity;
  char location[100];
  char *created_at;
  char *updated_at;
} Stock;

// Stock service functions
void init_stock(void);
void stock_add(Stock *stock);
void stock_update(Stock *stock);
void stock_delete(int id);

Stock *stock_get_by_id(int id);
GList *stock_get_all(void);
GList *stock_search(const char *query);

// File operations
gboolean stock_save_to_file(GList *stocks);
GList *stock_load_from_file(void);

#endif // STOCK_H
