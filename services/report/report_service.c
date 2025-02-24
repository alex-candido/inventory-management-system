#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "product.h"
#include "stock.h"
#include "report.h"

// Helper function to get current timestamp
static char* get_current_timestamp() {
    time_t now = time(NULL);
    return ctime(&now);
}

// Report 1: Out of Stock Products Report
GList* report_out_of_stock_products(int min_quantity) {
    GList *stocks = stock_get_all();
    GList *products = product_get_all();
    GList *out_of_stock = NULL;

    for (GList *stock_item = stocks; stock_item; stock_item = stock_item->next) {
        Stock *stock = stock_item->data;
        if (stock->quantity <= min_quantity) {
            for (GList *prod_item = products; prod_item; prod_item = prod_item->next) {
                Product *product = prod_item->data;
                if (product->id == stock->product_id) {
                    ReportOutOfStock *report = g_new(ReportOutOfStock, 1);
                    report->product_name = g_strdup(product->name);
                    report->category = g_strdup(product->category);
                    report->quantity = stock->quantity;
                    report->updated_at = g_strdup(stock->updated_at);
                    out_of_stock = g_list_append(out_of_stock, report);
                    break;
                }
            }
        }
    }

    return out_of_stock;
}

// Report 2: Products by Location Report
GList* report_products_by_location() {
    GList *stocks = stock_get_all();
    GList *products = product_get_all();
    GList *location_reports = NULL;
    GHashTable *location_hash = g_hash_table_new(g_str_hash, g_str_equal);

    // Group products by location
    for (GList *stock_item = stocks; stock_item; stock_item = stock_item->next) {
        Stock *stock = stock_item->data;
        GList *location_products = g_hash_table_lookup(location_hash, stock->location);

        ReportLocationProduct *loc_prod = g_new(ReportLocationProduct, 1);
        for (GList *prod_item = products; prod_item != NULL; prod_item = prod_item->next) {
            Product *product = prod_item->data;
            if (product->id == stock->product_id) {
                loc_prod->product_name = g_strdup(product->name);
                loc_prod->quantity = stock->quantity;
                break;
            }
        }

        location_products = g_list_append(location_products, loc_prod);
        g_hash_table_insert(location_hash, stock->location, location_products);
    }

    // Convert hash table to report list
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, location_hash);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        ReportLocation *report = g_new(ReportLocation, 1);
        report->location = g_strdup(key);
        report->products = value;
        location_reports = g_list_append(location_reports, report);
    }

    g_hash_table_destroy(location_hash);
    return location_reports;
}

// Helper function to compare products by creation date
static gint compare_created_at(ReportRecentProduct *a, ReportRecentProduct *b) {
    return g_strcmp0(b->created_at, a->created_at);  // Sort in descending order (newest first)
}

// Report 3: Recently Added Products Report
GList* report_recent_products() {
    GList *products = product_get_all();
    GList *recent_products = NULL;

    // Copy products to a new list for sorting
    for (GList *item = products; item; item = item->next) {
        Product *product = item->data;
        ReportRecentProduct *report = g_new(ReportRecentProduct, 1);
        report->name = g_strdup(product->name);
        report->category = g_strdup(product->category);
        report->created_at = g_strdup(product->created_at);
        recent_products = g_list_append(recent_products, report);
    }

    // Sort by created_at (assuming newer dates are "greater")
    recent_products = g_list_sort(recent_products, (GCompareFunc)compare_created_at);
    return recent_products;
}

// Report 6: Products by Category Report
GList* report_products_by_category() {
    GList *products = product_get_all();
    GList *stocks = stock_get_all();
    GList *category_reports = NULL;
    GHashTable *category_hash = g_hash_table_new(g_str_hash, g_str_equal);

    // Initialize category statistics
    for (GList *prod_item = products; prod_item; prod_item = prod_item->next) {
        Product *product = prod_item->data;
        ReportCategory *cat_stat = g_hash_table_lookup(category_hash, product->category);
        
        if (!cat_stat) {
            cat_stat = g_new(ReportCategory, 1);
            cat_stat->category = g_strdup(product->category);
            cat_stat->total_quantity = 0;
            cat_stat->total_price = 0.0;
            cat_stat->product_count = 0;
            g_hash_table_insert(category_hash, product->category, cat_stat);
        }

        // Find stock quantity for this product
        for (GList *stock_item = stocks; stock_item; stock_item = stock_item->next) {
            Stock *stock = stock_item->data;
            if (stock->product_id == product->id) {
                cat_stat->total_quantity += stock->quantity;
                break;
            }
        }

        cat_stat->total_price += product->price;
        cat_stat->product_count++;
    }

    // Convert hash table to list
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, category_hash);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        ReportCategory *cat_stat = value;
        cat_stat->avg_price = cat_stat->total_price / cat_stat->product_count;
        category_reports = g_list_append(category_reports, cat_stat);
    }

    g_hash_table_destroy(category_hash);
    return category_reports;
}

// Report 7: Stock Valuation Report
ReportValuation* report_stock_valuation() {
    GList *products = product_get_all();
    GList *stocks = stock_get_all();
    ReportValuation *report = g_new(ReportValuation, 1);
    report->total_value = 0.0;
    report->total_items = 0;
    report->generated_at = g_strdup(get_current_timestamp());

    for (GList *stock_item = stocks; stock_item; stock_item = stock_item->next) {
        Stock *stock = stock_item->data;
        for (GList *prod_item = products; prod_item; prod_item = prod_item->next) {
            Product *product = prod_item->data;
            if (product->id == stock->product_id) {
                report->total_value += product->price * stock->quantity;
                report->total_items += stock->quantity;
                break;
            }
        }
    }

    return report;
}

// Memory management functions
void report_free_out_of_stock(GList *report) {
    g_list_free_full(report, (GDestroyNotify)report_free_out_of_stock_item);
}

void report_free_out_of_stock_item(ReportOutOfStock *item) {
    if (item) {
        g_free(item->product_name);
        g_free(item->category);
        g_free(item->updated_at);
        g_free(item);
    }
}

void report_free_location(GList *report) {
    g_list_free_full(report, (GDestroyNotify)report_free_location_item);
}

void report_free_location_item(ReportLocation *item) {
    if (item) {
        g_free(item->location);
        g_list_free_full(item->products, (GDestroyNotify)report_free_location_product);
        g_free(item);
    }
}

void report_free_location_product(ReportLocationProduct *item) {
    if (item) {
        g_free(item->product_name);
        g_free(item);
    }
}

void report_free_recent_products(GList *report) {
    g_list_free_full(report, (GDestroyNotify)report_free_recent_product);
}

void report_free_recent_product(ReportRecentProduct *item) {
    if (item) {
        g_free(item->name);
        g_free(item->category);
        g_free(item->created_at);
        g_free(item);
    }
}

void report_free_category(GList *report) {
    g_list_free_full(report, (GDestroyNotify)report_free_category_item);
}

void report_free_category_item(ReportCategory *item) {
    if (item) {
        g_free(item->category);
        g_free(item);
    }
}

void report_free_valuation(ReportValuation *report) {
    if (report) {
        g_free(report->generated_at);
        g_free(report);
    }
}