#ifndef PRODUCT_H
#define PRODUCT_H

void create_product(const char *name, const char *category, double price);
void read_products();
void update_product(int id, const char *name, const char *category, double price);
void delete_product(int id);

#endif
