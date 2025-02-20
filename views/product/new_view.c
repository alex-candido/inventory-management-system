#include <gtk/gtk.h>
#include "views/product/new_view.h"

void show_product_new(GtkWidget *content_area)
{
  // Limpa a área de conteúdo antes de adicionar o novo conteúdo
  GList *children = gtk_container_get_children(GTK_CONTAINER(content_area));
  for (GList *iter = children; iter != NULL; iter = g_list_next(iter))
  {
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  }
  g_list_free(children);

  // Cria o conteúdo da tela de criação de novo produto
  GtkWidget *label = gtk_label_new("Product New");

  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}
