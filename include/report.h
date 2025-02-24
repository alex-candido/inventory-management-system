#ifndef REPORT_H
#define REPORT_H

#include <gtk/gtk.h>

// Report 1: Out of Stock Products
typedef struct
{
  char *product_name;
  char *category;
  int quantity;
  char *updated_at;
} ReportOutOfStock;

// Report 2: Products by Location
typedef struct
{
  char *product_name;
  int quantity;
} ReportLocationProduct;

typedef struct
{
  char *location;
  GList *products; // List of ReportLocationProduct
} ReportLocation;

// Report 3: Recent Products
typedef struct
{
  char *name;
  char *category;
  char *created_at;
} ReportRecentProduct;

// Report 6: Products by Category
typedef struct
{
  char *category;
  int total_quantity;
  double total_price;
  double avg_price;
  int product_count;
} ReportCategory;

// Report 7: Stock Valuation
typedef struct
{
  double total_value;
  int total_items;
  char *generated_at;
} ReportValuation;

// Report generation functions
GList *report_out_of_stock_products(int min_quantity);
GList *report_products_by_location(void);
GList *report_recent_products(void);
GList *report_products_by_category(void);
ReportValuation *report_stock_valuation(void);

// Memory management functions
void report_free_out_of_stock(GList *report);
void report_free_out_of_stock_item(ReportOutOfStock *item);
void report_free_location(GList *report);
void report_free_location_item(ReportLocation *item);
void report_free_location_product(ReportLocationProduct *item);
void report_free_recent_products(GList *report);
void report_free_recent_product(ReportRecentProduct *item);
void report_free_category(GList *report);
void report_free_category_item(ReportCategory *item);
void report_free_valuation(ReportValuation *report);

#endif // REPORT_H
