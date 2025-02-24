#include <gtk/gtk.h>
#include "stock.h"
#include "product.h"

typedef struct
{
    GtkWidget *dialog;
    GtkWidget *product_id_entry;
    GtkWidget *quantity_entry;
    GtkWidget *location_entry;
    Stock *stock;
    gboolean is_edit_mode;
} StockDialog;

static void on_response(GtkDialog *dialog, gint response_id, StockDialog *data)
{
    if (response_id == GTK_RESPONSE_OK)
    {
        // Get values from entriesP
        const char *product_id_str = gtk_entry_get_text(GTK_ENTRY(data->product_id_entry));
        const char *quantity_str = gtk_entry_get_text(GTK_ENTRY(data->quantity_entry));
        const char *location = gtk_entry_get_text(GTK_ENTRY(data->location_entry));

        int product_id = atoi(product_id_str);
        int quantity = atoi(quantity_str);

        if (data->is_edit_mode)
        {
            // Update existing stock
            data->stock->product_id = product_id;
            data->stock->quantity = quantity;
            strncpy(data->stock->location, location, sizeof(data->stock->location) - 1);
            data->stock->location[sizeof(data->stock->location) - 1] = '\0';

            stock_update(data->stock);
        }
        else
        {
            // Create new stock
            Stock new_stock = {0};
            new_stock.product_id = product_id;
            new_stock.quantity = quantity;
            strncpy(new_stock.location, location, sizeof(new_stock.location) - 1);
            new_stock.location[sizeof(new_stock.location) - 1] = '\0';

            stock_add(&new_stock);
        }
    }

    gtk_widget_destroy(GTK_WIDGET(dialog));
}

static GtkWidget *create_form_grid()
{
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_widget_set_margin_start(grid, 10);
    gtk_widget_set_margin_end(grid, 10);
    gtk_widget_set_margin_top(grid, 10);
    gtk_widget_set_margin_bottom(grid, 10);

    return grid;
}

static void add_form_row(GtkWidget *grid, const char *label_text, GtkWidget *entry, int row)
{
    GtkWidget *label = gtk_label_new(label_text);
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_grid_attach(GTK_GRID(grid), label, 0, row, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry, 1, row, 1, 1);
    gtk_widget_set_hexpand(entry, TRUE);
}

void show_stock_dialog(GtkWindow *parent, Stock *stock)
{
    StockDialog *data = g_new0(StockDialog, 1);
    data->stock = stock;
    data->is_edit_mode = (stock != NULL);

    // Create dialog
    data->dialog = gtk_dialog_new_with_buttons(
        data->is_edit_mode ? "Edit Stock Entry" : "New Stock Entry",
        parent,
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Save", GTK_RESPONSE_OK,
        NULL);

    // Create form fields
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(data->dialog));
    GtkWidget *grid = create_form_grid();

    data->product_id_entry = gtk_entry_new();
    data->quantity_entry = gtk_entry_new();
    data->location_entry = gtk_entry_new();

    // Set field values if editing
    if (data->is_edit_mode)
    {
        char product_id_str[32];
        snprintf(product_id_str, sizeof(product_id_str), "%d", stock->product_id);
        gtk_entry_set_text(GTK_ENTRY(data->product_id_entry), product_id_str);

        char quantity_str[32];
        snprintf(quantity_str, sizeof(quantity_str), "%d", stock->quantity);
        gtk_entry_set_text(GTK_ENTRY(data->quantity_entry), quantity_str);

        gtk_entry_set_text(GTK_ENTRY(data->location_entry), stock->location);
    }

    // Add fields to grid
    add_form_row(grid, "Product ID:", data->product_id_entry, 0);
    add_form_row(grid, "Quantity:", data->quantity_entry, 1);
    add_form_row(grid, "Location:", data->location_entry, 2);

    gtk_container_add(GTK_CONTAINER(content_area), grid);

    // Connect signals
    g_signal_connect(data->dialog, "response", G_CALLBACK(on_response), data);
    g_signal_connect_swapped(data->dialog, "destroy", G_CALLBACK(g_free), data);

    gtk_widget_show_all(data->dialog);
}