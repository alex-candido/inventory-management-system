#include <stdio.h>
#include <stdlib.h>
#include "product.h"
#include "stock.h"

int main()
{
  int option;

  printf("Welcome to the Inventory Management System\n");
  printf("1. Manage Products\n");
  printf("2. Manage Stock\n");
  printf("3. Exit\n");

  if (scanf("%d", &option) != 1)
  {
    printf("Invalid input. Exiting.\n");
    return 1;
  }

  if (option == 1)
  {
    int product_option;
    printf("1. Create Product\n");
    printf("2. Read Products\n");
    printf("3. Update Product\n");
    printf("4. Delete Product\n");
    printf("5. Exit\n");
    if (scanf("%d", &product_option) != 1)
    {
      printf("Invalid input. Exiting.\n");
      return 1;
    }

    if (product_option == 1)
    {
      char name[255], category[255];
      double price;
      printf("Enter product name: ");
      if (scanf("%254s", name) != 1)
        return 1;
      printf("Enter product category: ");
      if (scanf("%254s", category) != 1)
        return 1;
      printf("Enter product price: ");
      if (scanf("%lf", &price) != 1)
        return 1;
      create_product(name, category, price);
    }
    else if (product_option == 2)
    {
      read_products();
    }
    else if (product_option == 3)
    {
      int id;
      char name[255], category[255];
      double price;
      printf("Enter product ID to update: ");
      if (scanf("%d", &id) != 1)
        return 1;
      printf("Enter new product name: ");
      if (scanf("%254s", name) != 1)
        return 1;
      printf("Enter new product category: ");
      if (scanf("%254s", category) != 1)
        return 1;
      printf("Enter new product price: ");
      if (scanf("%lf", &price) != 1)
        return 1;
      update_product(id, name, category, price);
    }
    else if (product_option == 4)
    {
      int id;
      printf("Enter product ID to delete: ");
      if (scanf("%d", &id) != 1)
        return 1;
      delete_product(id);
    }
  }
  else if (option == 2)
  {
    int stock_option;
    printf("1. Create Stock\n");
    printf("2. Read Stock\n");
    printf("3. Update Stock\n");
    printf("4. Delete Stock\n");
    printf("5. Exit\n");
    if (scanf("%d", &stock_option) != 1)
      return 1;

    if (stock_option == 1)
    {
      int product_id, quantity;
      char location[255];
      printf("Enter product ID: ");
      if (scanf("%d", &product_id) != 1)
        return 1;
      printf("Enter quantity: ");
      if (scanf("%d", &quantity) != 1)
        return 1;
      printf("Enter stock location: ");
      if (scanf("%254s", location) != 1)
        return 1;
      create_stock(product_id, quantity, location);
    }
    else if (stock_option == 2)
    {
      int product_id;
      printf("Enter product ID to view stock: ");
      if (scanf("%d", &product_id) != 1)
        return 1;
      read_stock(product_id);
    }
    else if (stock_option == 3)
    {
      int product_id, quantity;
      char location[255];
      printf("Enter product ID to update stock: ");
      if (scanf("%d", &product_id) != 1)
        return 1;
      printf("Enter new quantity: ");
      if (scanf("%d", &quantity) != 1)
        return 1;
      printf("Enter new location: ");
      if (scanf("%254s", location) != 1)
        return 1;
      update_stock(product_id, quantity, location);
    }
    else if (stock_option == 4)
    {
      int product_id;
      printf("Enter product ID to delete stock: ");
      if (scanf("%d", &product_id) != 1)
        return 1;
      delete_stock(product_id);
    }
  }

  return 0;
}
