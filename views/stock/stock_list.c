#include <gtk/gtk.h>
#include "stock.h"
#include "stock_dialog.h"

static GtkWidget *list_box;
static GtkWidget *search_entry;

static void on_edit_clicked(GtkButton *button, Stock *stock);

// Função wrapper para gtk_widget_destroy
static void destroy_widget_wrapper(void *widget, void *user_data)
{
    (void)user_data;
    gtk_widget_destroy(GTK_WIDGET(widget));
}

static void refresh_stock_list(void)
{
    // Clear existing items
    GList *children = gtk_container_get_children(GTK_CONTAINER(list_box));
    g_list_foreach(children, (GFunc)destroy_widget_wrapper, NULL);
    g_list_free(children);

    // Get search query
    const char *query = gtk_entry_get_text(GTK_ENTRY(search_entry));
    GList *stocks = stock_search(query);

    // Create table headers
    GtkWidget *header_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_start(header_row, 10);
    gtk_widget_set_margin_end(header_row, 10);
    gtk_widget_set_margin_top(header_row, 5);
    gtk_widget_set_margin_bottom(header_row, 5);

    const char *headers[] = {"ID", "Product ID", "Quantity", "Location", "Update At", "Actions"};
    double column_weights[] = {0.1, 0.15, 0.15, 0.2, 0.2, 0.2};

    for (int i = 0; i < 6; i++)
    {
        GtkWidget *header = gtk_label_new(headers[i]);
        gtk_widget_set_hexpand(header, TRUE);
        gtk_label_set_xalign(GTK_LABEL(header), 0.0);
        gtk_widget_set_size_request(header, 100, -1);
        gtk_box_pack_start(GTK_BOX(header_row), header, column_weights[i], TRUE, 0);

        // Make headers bold
        PangoAttrList *attr_list = pango_attr_list_new();
        pango_attr_list_insert(attr_list, pango_attr_weight_new(PANGO_WEIGHT_BOLD));
        gtk_label_set_attributes(GTK_LABEL(header), attr_list);
        pango_attr_list_unref(attr_list);
    }

    gtk_container_add(GTK_CONTAINER(list_box), header_row);
    gtk_widget_show_all(header_row);

    // Add stock items to the list
    for (GList *item = stocks; item != NULL; item = item->next)
    {
        Stock *stock = item->data;

        // Create row container
        GtkWidget *row_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
        gtk_widget_set_margin_start(row_box, 10);
        gtk_widget_set_margin_end(row_box, 10);
        gtk_widget_set_margin_top(row_box, 5);
        gtk_widget_set_margin_bottom(row_box, 5);

        // Stock ID
        char stock_id_str[32];
        snprintf(stock_id_str, sizeof(stock_id_str), "%d", stock->id);
        GtkWidget *stock_id_label = gtk_label_new(stock_id_str);
        gtk_label_set_xalign(GTK_LABEL(stock_id_label), 0.0);
        gtk_widget_set_hexpand(stock_id_label, TRUE);
        gtk_box_pack_start(GTK_BOX(row_box), stock_id_label, 0.1, TRUE, 0);

        // Product ID
        char product_id_str[32];
        snprintf(product_id_str, sizeof(product_id_str), "%d", stock->product_id);
        GtkWidget *product_id_label = gtk_label_new(product_id_str);
        gtk_label_set_xalign(GTK_LABEL(product_id_label), 0.0);
        gtk_widget_set_hexpand(product_id_label, TRUE);
        gtk_box_pack_start(GTK_BOX(row_box), product_id_label, 0.15, TRUE, 0);

        // Quantity
        char qty_str[32];
        snprintf(qty_str, sizeof(qty_str), "%d", stock->quantity);
        GtkWidget *qty_label = gtk_label_new(qty_str);
        gtk_label_set_xalign(GTK_LABEL(qty_label), 0.0);
        gtk_widget_set_hexpand(qty_label, TRUE);
        gtk_box_pack_start(GTK_BOX(row_box), qty_label, 0.15, TRUE, 0);

        // Location
        GtkWidget *location_label = gtk_label_new(stock->location);
        gtk_label_set_xalign(GTK_LABEL(location_label), 0.0);
        gtk_widget_set_hexpand(location_label, TRUE);
        gtk_box_pack_start(GTK_BOX(row_box), location_label, 0.25, TRUE, 0);

        // Last Update
        const char *updated_time = stock->updated_at ? stock->updated_at : "N/A";
        GtkWidget *update_label = gtk_label_new(updated_time);
        gtk_label_set_xalign(GTK_LABEL(update_label), 0.0);
        gtk_widget_set_hexpand(update_label, TRUE);
        gtk_box_pack_start(GTK_BOX(row_box), update_label, 0.2, TRUE, 0);

        // Action buttons
        GtkWidget *actions_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        gtk_widget_set_hexpand(actions_box, TRUE);

        GtkWidget *edit_btn = gtk_button_new_from_icon_name("document-edit-symbolic", GTK_ICON_SIZE_BUTTON);
        GtkWidget *delete_btn = gtk_button_new_from_icon_name("edit-delete-symbolic", GTK_ICON_SIZE_BUTTON);

        gtk_box_pack_start(GTK_BOX(actions_box), edit_btn, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(actions_box), delete_btn, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(row_box), actions_box, 0.2, TRUE, 0);

        // Add row to list
        gtk_container_add(GTK_CONTAINER(list_box), row_box);
        gtk_widget_show_all(row_box);

        // Connect signals
        g_signal_connect_swapped(delete_btn, "clicked", G_CALLBACK(stock_delete), GINT_TO_POINTER(stock->id));
        g_signal_connect_swapped(delete_btn, "clicked", G_CALLBACK(refresh_stock_list), NULL);
        g_signal_connect(edit_btn, "clicked", G_CALLBACK(on_edit_clicked), stock);
    }

    if (stocks != stock_get_all())
    {
        g_list_free(stocks);
    }
}

static void on_search_changed(GtkSearchEntry *entry, gpointer user_data)
{
    (void)entry;
    (void)user_data;
    refresh_stock_list();
}

static void on_edit_clicked(GtkButton *button, Stock *stock)
{
    (void)button;
    (void)stock;

    show_stock_dialog(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))), stock);
    refresh_stock_list();
}

static void on_add_clicked(GtkButton *button, gpointer user_data)
{
    (void)button;
    (void)user_data;

    show_stock_dialog(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))), NULL);
    refresh_stock_list();
}

GtkWidget *create_stock_list_view()
{
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Toolbar
    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_start(toolbar, 10);
    gtk_widget_set_margin_end(toolbar, 10);
    gtk_widget_set_margin_top(toolbar, 10);
    gtk_widget_set_margin_bottom(toolbar, 10);

    // Search entry
    search_entry = gtk_search_entry_new();
    gtk_widget_set_size_request(search_entry, 300, -1);

    // Add button
    GtkWidget *add_btn = gtk_button_new_with_label("New Stock");
    gtk_style_context_add_class(gtk_widget_get_style_context(add_btn), "suggested-action");

    gtk_box_pack_start(GTK_BOX(toolbar), search_entry, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(toolbar), add_btn, FALSE, FALSE, 0);

    // List box
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                   GTK_POLICY_NEVER,
                                   GTK_POLICY_AUTOMATIC);
    gtk_widget_set_vexpand(scrolled, TRUE);
    gtk_widget_set_hexpand(scrolled, TRUE);

    list_box = gtk_list_box_new();
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(list_box), GTK_SELECTION_NONE);
    gtk_container_add(GTK_CONTAINER(scrolled), list_box);

    gtk_box_pack_start(GTK_BOX(main_box), toolbar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), scrolled, TRUE, TRUE, 0);

    // Connect signals
    g_signal_connect(add_btn, "clicked", G_CALLBACK(on_add_clicked), NULL);

    // Initial load
    refresh_stock_list();

    g_signal_connect(search_entry, "search-changed", G_CALLBACK(on_search_changed), NULL);

    return main_box;
}
