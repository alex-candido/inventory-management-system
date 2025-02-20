#include <gtk/gtk.h>
#include "views/stock/edit_view.h"

// Função para exibir a edição de estoque
void show_stock_edit(GtkWidget *content_area)
{
  GtkWidget *label = gtk_label_new("Stock Edit");
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}
