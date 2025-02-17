#ifndef STOCK_H
#define STOCK_H

void create_stock(int product_id, int quantity, const char *location);
void read_stock(int product_id);
void update_stock(int product_id, int quantity, const char *location);
void delete_stock(int product_id);

#endif // STOCK_H
