#include <gtk/gtk.h>
#include "product.h"
#include "product_dialog.h"

static GtkWidget *list_box;
static GtkWidget *search_entry;

static void on_edit_clicked(GtkButton *button, Product *product);

// Wrapper function for gtk_widget_destroy
static void destroy_widget_wrapper(void *widget, void *user_data)
{
    (void)user_data;
    gtk_widget_destroy(GTK_WIDGET(widget));
}

static void refresh_product_list(void)
{
    // Clear existing items
    GList *children = gtk_container_get_children(GTK_CONTAINER(list_box));
    g_list_foreach(children, (GFunc)destroy_widget_wrapper, NULL);
    g_list_free(children);

    // Get search query
    const char *query = gtk_entry_get_text(GTK_ENTRY(search_entry));
    GList *products = product_search(query);

    // Create table headers
    GtkWidget *header_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_start(header_row, 10);
    gtk_widget_set_margin_end(header_row, 10);
    gtk_widget_set_margin_top(header_row, 5);
    gtk_widget_set_margin_bottom(header_row, 5);

    const char *headers[] = {"ID", "Name", "Price", "Quantity", "Category", "Actions"};
    double column_weights[] = {0.08, 0.25, 0.15, 0.12, 0.25, 0.15};

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

    // Add product items to the list
    for (GList *item = products; item != NULL; item = item->next)
    {
        Product *product = item->data;

        // Create row container with separator
        GtkWidget *row_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        GtkWidget *row_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
        gtk_widget_set_margin_start(row_box, 10);
        gtk_widget_set_margin_end(row_box, 10);
        gtk_widget_set_margin_top(row_box, 8);
        gtk_widget_set_margin_bottom(row_box, 8);

        // Add separator
        GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
        gtk_widget_set_margin_top(separator, 0);
        gtk_widget_set_margin_bottom(separator, 0);

        // Product ID
        char id_str[32];
        snprintf(id_str, sizeof(id_str), "%d", product->id);
        GtkWidget *id_label = gtk_label_new(id_str);
        gtk_label_set_xalign(GTK_LABEL(id_label), 0.0);
        gtk_widget_set_hexpand(id_label, TRUE);
        gtk_box_pack_start(GTK_BOX(row_box), id_label, 0.1, TRUE, 0);

        // Product name
        GtkWidget *name_label = gtk_label_new(product->name);
        gtk_label_set_xalign(GTK_LABEL(name_label), 0.0);
        gtk_widget_set_hexpand(name_label, TRUE);
        gtk_box_pack_start(GTK_BOX(row_box), name_label, 0.3, TRUE, 0);

        // Price
        char price_str[32];
        snprintf(price_str, sizeof(price_str), "R$ %.2f", product->price);
        GtkWidget *price_label = gtk_label_new(price_str);
        gtk_label_set_xalign(GTK_LABEL(price_label), 0.0);
        gtk_widget_set_hexpand(price_label, TRUE);
        gtk_box_pack_start(GTK_BOX(row_box), price_label, 0.15, TRUE, 0);

        // Quantity
        char qty_str[32];
        snprintf(qty_str, sizeof(qty_str), "%d", product->quantity);
        GtkWidget *qty_label = gtk_label_new(qty_str);
        gtk_label_set_xalign(GTK_LABEL(qty_label), 0.0);
        gtk_widget_set_hexpand(qty_label, TRUE);
        gtk_box_pack_start(GTK_BOX(row_box), qty_label, 0.15, TRUE, 0);

        // Category
        GtkWidget *category_label = gtk_label_new(product->category);
        gtk_label_set_xalign(GTK_LABEL(category_label), 0.0);
        gtk_widget_set_hexpand(category_label, TRUE);
        gtk_box_pack_start(GTK_BOX(row_box), category_label, 0.2, TRUE, 0);

        // Action buttons
        GtkWidget *actions_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        gtk_widget_set_hexpand(actions_box, TRUE);

        GtkWidget *edit_btn = gtk_button_new_from_icon_name("document-edit-symbolic", GTK_ICON_SIZE_BUTTON);
        GtkWidget *delete_btn = gtk_button_new_from_icon_name("edit-delete-symbolic", GTK_ICON_SIZE_BUTTON);

        gtk_box_pack_start(GTK_BOX(actions_box), edit_btn, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(actions_box), delete_btn, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(row_box), actions_box, 0.2, TRUE, 0);

        // Add row and separator to container
        gtk_container_add(GTK_CONTAINER(row_container), row_box);
        gtk_container_add(GTK_CONTAINER(row_container), separator);

        // Add container to list
        gtk_container_add(GTK_CONTAINER(list_box), row_container);
        gtk_widget_show_all(row_container);

        // Connect signals
        g_signal_connect_swapped(delete_btn, "clicked", G_CALLBACK(product_delete), GINT_TO_POINTER(product->id));
        g_signal_connect_swapped(delete_btn, "clicked", G_CALLBACK(refresh_product_list), NULL);
        g_signal_connect(edit_btn, "clicked", G_CALLBACK(on_edit_clicked), product);
    }

    if (products != product_get_all())
    {
        g_list_free(products);
    }
}

static void on_search_changed(GtkSearchEntry *entry, gpointer user_data)
{
    (void)entry;
    (void)user_data;
    refresh_product_list();
}

static void on_edit_clicked(GtkButton *button, Product *product)
{
    (void)button;
    (void)product;

    show_product_dialog(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))), product);
    refresh_product_list();
}

static void on_add_clicked(GtkButton *button, gpointer user_data)
{
    (void)button;
    (void)user_data;

    show_product_dialog(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))), NULL);
    refresh_product_list();
}

GtkWidget *create_product_list_view()
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
    GtkWidget *add_btn = gtk_button_new_with_label("New Product");
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
    refresh_product_list();

    g_signal_connect(search_entry, "search-changed", G_CALLBACK(on_search_changed), NULL);

    return main_box;
}