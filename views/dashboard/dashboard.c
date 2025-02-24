#include <gtk/gtk.h>
#include "product.h"
#include "stock.h"
#include "report.h"

static GtkWidget *create_summary_card(const char *title, const char *value)
{
    GtkWidget *card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_margin_start(card, 10);
    gtk_widget_set_margin_end(card, 10);
    gtk_widget_set_margin_top(card, 10);
    gtk_widget_set_margin_bottom(card, 10);

    // Add border and background
    GtkStyleContext *context = gtk_widget_get_style_context(card);
    gtk_style_context_add_class(context, "card");

    // Title
    GtkWidget *title_label = gtk_label_new(title);
    gtk_label_set_xalign(GTK_LABEL(title_label), 0.0);
    gtk_widget_set_margin_bottom(title_label, 5);

    // Value
    GtkWidget *value_label = gtk_label_new(value);
    gtk_label_set_xalign(GTK_LABEL(value_label), 0.0);
    PangoAttrList *attr_list = pango_attr_list_new();
    pango_attr_list_insert(attr_list, pango_attr_weight_new(PANGO_WEIGHT_BOLD));
    pango_attr_list_insert(attr_list, pango_attr_scale_new(1.5));
    gtk_label_set_attributes(GTK_LABEL(value_label), attr_list);
    pango_attr_list_unref(attr_list);

    gtk_container_add(GTK_CONTAINER(card), title_label);
    gtk_container_add(GTK_CONTAINER(card), value_label);

    return card;
}

static void destroy_widget_wrapper(void *widget, void *user_data)
{
    (void)user_data;
    gtk_widget_destroy(GTK_WIDGET(widget));
}

static void update_dashboard(GtkWidget *grid)
{
    // Get statistics
    GList *products = product_get_all();
    GList *stocks = stock_get_all();
    GList *low_stock = report_out_of_stock_products(5);
    ReportValuation *valuation = report_stock_valuation();

    int total_products = g_list_length(products);
    int total_stock_entries = g_list_length(stocks);
    int low_stock_count = g_list_length(low_stock);

    // Calculate total items in stock
    int total_items = 0;
    for (GList *item = stocks; item != NULL; item = item->next)
    {
        Stock *stock = item->data;
        total_items += stock->quantity;
    }

    // Update summary cards
    char products_str[32], entries_str[32], items_str[32], value_str[64], low_stock_str[32];
    snprintf(products_str, sizeof(products_str), "%d", total_products);
    snprintf(entries_str, sizeof(entries_str), "%d", total_stock_entries);
    snprintf(items_str, sizeof(items_str), "%d", total_items);
    snprintf(value_str, sizeof(value_str), "R$ %.2f", valuation->total_value);
    snprintf(low_stock_str, sizeof(low_stock_str), "%d", low_stock_count);

    // Clear existing widgets
    GList *children = gtk_container_get_children(GTK_CONTAINER(grid));
    g_list_foreach(children, (GFunc)destroy_widget_wrapper, NULL);
    g_list_free(children);

    // Add new summary cards - First row
    gtk_grid_attach(GTK_GRID(grid),
                    create_summary_card("Total Products", products_str),
                    0, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grid),
                    create_summary_card("Stock Entries", entries_str),
                    1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grid),
                    create_summary_card("Total Items", items_str),
                    2, 0, 1, 1);

    // Second row
    gtk_grid_attach(GTK_GRID(grid),
                    create_summary_card("Total Stock Value", value_str),
                    0, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(grid),
                    create_summary_card("Low Stock Items", low_stock_str),
                    1, 1, 1, 1);

    gtk_widget_show_all(grid);

    // Free resources
    report_free_out_of_stock(low_stock);
    report_free_valuation(valuation);
}

GtkWidget *create_dashboard_view()
{
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Title
    GtkWidget *title = gtk_label_new("Dashboard");
    PangoAttrList *attr_list = pango_attr_list_new();
    pango_attr_list_insert(attr_list, pango_attr_weight_new(PANGO_WEIGHT_BOLD));
    pango_attr_list_insert(attr_list, pango_attr_scale_new(2.0));
    gtk_label_set_attributes(GTK_LABEL(title), attr_list);
    pango_attr_list_unref(attr_list);

    gtk_widget_set_margin_top(title, 20);
    gtk_widget_set_margin_bottom(title, 20);

    // Grid for summary cards
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_widget_set_margin_start(grid, 10);
    gtk_widget_set_margin_end(grid, 10);

    gtk_box_pack_start(GTK_BOX(main_box), title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), grid, TRUE, TRUE, 0);

    // Initial update
    update_dashboard(grid);

    return main_box;
}
