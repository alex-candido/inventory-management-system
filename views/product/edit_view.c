#include <gtk/gtk.h>
#include "../../include/views/product/edit_view.h"

// Função para exibir a edição de produtos
void show_product_edit(GtkWidget *content_area)
{
  GtkWidget *label = gtk_label_new("Product Edit");
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}
