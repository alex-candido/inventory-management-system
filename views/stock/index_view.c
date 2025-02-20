#include <gtk/gtk.h>
#include "views/stock/index_view.h"

// Função para exibir o índice de estoque
void show_stock_index(GtkWidget *content_area)
{
  // Remove os widgets anteriores
  GList *children, *iter;
  children = gtk_container_get_children(GTK_CONTAINER(content_area));
  for (iter = children; iter != NULL; iter = g_list_next(iter))
  {
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  }
  g_list_free(children);

  // Adiciona novo conteúdo
  GtkWidget *label = gtk_label_new("Stock Index");
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}
