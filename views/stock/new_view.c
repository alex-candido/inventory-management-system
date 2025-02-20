#include <gtk/gtk.h>
#include "views/stock/edit_view.h"

void show_stock_new(GtkWidget *content_area)
{
  GtkWidget *label = gtk_label_new("Stock New");
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}
