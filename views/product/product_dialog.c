#include <gtk/gtk.h>
#include "product.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
  GtkWidget *dialog;
  GtkWidget *name_entry;
  GtkWidget *description_entry;
  GtkWidget *price_entry;
  GtkWidget *quantity_entry;
  GtkWidget *category_entry;
  Product *product;
  gboolean is_edit_mode;
} ProductDialog;

static void on_response(GtkDialog *dialog, gint response_id, ProductDialog *data)
{
  if (response_id == GTK_RESPONSE_OK)
  {
    const char *name = gtk_entry_get_text(GTK_ENTRY(data->name_entry));
    const char *description = gtk_entry_get_text(GTK_ENTRY(data->description_entry));
    const char *price_str = gtk_entry_get_text(GTK_ENTRY(data->price_entry));
    const char *quantity_str = gtk_entry_get_text(GTK_ENTRY(data->quantity_entry));
    const char *category = gtk_entry_get_text(GTK_ENTRY(data->category_entry));

    double price = g_ascii_strtod(price_str, NULL);
    int quantity = atoi(quantity_str);

    if (data->is_edit_mode)
    {
      data->product->price = price;
      data->product->quantity = quantity;
      strncpy(data->product->name, name, sizeof(data->product->name) - 1);
      data->product->name[sizeof(data->product->name) - 1] = '\0';
      strncpy(data->product->description, description, sizeof(data->product->description) - 1);
      data->product->description[sizeof(data->product->description) - 1] = '\0';
      strncpy(data->product->category, category, sizeof(data->product->category) - 1);
      data->product->category[sizeof(data->product->category) - 1] = '\0';

      product_update(data->product);
    }
    else
    {
      Product new_product = {0};
      strncpy(new_product.name, name, sizeof(new_product.name) - 1);
      new_product.name[sizeof(new_product.name) - 1] = '\0';
      strncpy(new_product.description, description, sizeof(new_product.description) - 1);
      new_product.description[sizeof(new_product.description) - 1] = '\0';
      strncpy(new_product.category, category, sizeof(new_product.category) - 1);
      new_product.category[sizeof(new_product.category) - 1] = '\0';
      new_product.price = price;
      new_product.quantity = quantity;
      product_add(&new_product);
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

void show_product_dialog(GtkWindow *parent, Product *product)
{
  ProductDialog *data = g_new0(ProductDialog, 1);
  data->product = product;
  data->is_edit_mode = (product != NULL);

  data->dialog = gtk_dialog_new_with_buttons(
      data->is_edit_mode ? "Edit Product" : "New Product",
      parent,
      GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
      "_Cancel", GTK_RESPONSE_CANCEL,
      "_Save", GTK_RESPONSE_OK,
      NULL);

  GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(data->dialog));
  GtkWidget *grid = create_form_grid();

  data->name_entry = gtk_entry_new();
  data->description_entry = gtk_entry_new();
  data->price_entry = gtk_entry_new();
  data->quantity_entry = gtk_entry_new();
  data->category_entry = gtk_entry_new();

  if (data->is_edit_mode)
  {
    gtk_entry_set_text(GTK_ENTRY(data->name_entry), product->name);
    gtk_entry_set_text(GTK_ENTRY(data->description_entry), product->description);
    char price_str[32];
    snprintf(price_str, sizeof(price_str), "%.2f", product->price);
    gtk_entry_set_text(GTK_ENTRY(data->price_entry), price_str);
    char quantity_str[32];
    snprintf(quantity_str, sizeof(quantity_str), "%d", product->quantity);
    gtk_entry_set_text(GTK_ENTRY(data->quantity_entry), quantity_str);
    gtk_entry_set_text(GTK_ENTRY(data->category_entry), product->category);
  }

  add_form_row(grid, "Name:", data->name_entry, 0);
  add_form_row(grid, "Description:", data->description_entry, 1);
  add_form_row(grid, "Price:", data->price_entry, 2);
  add_form_row(grid, "Quantity:", data->quantity_entry, 3);
  add_form_row(grid, "Category:", data->category_entry, 4);

  gtk_container_add(GTK_CONTAINER(content_area), grid);

  g_signal_connect(data->dialog, "response", G_CALLBACK(on_response), data);
  g_signal_connect_swapped(data->dialog, "destroy", G_CALLBACK(g_free), data);

  gtk_widget_show_all(data->dialog);
}
