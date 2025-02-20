#include <gtk/gtk.h>
#include "views/dashboard/index_view.h"

// Função para exibir o dashboard
void show_dashboard(GtkWidget *content_area)
{
  // Remover todos os widgets filhos do content_area antes de adicionar novos
  GList *children, *iter;
  children = gtk_container_get_children(GTK_CONTAINER(content_area));
  for (iter = children; iter != NULL; iter = g_list_next(iter))
  {
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  }
  g_list_free(children);

  GtkWidget *label = gtk_label_new("Dashboard: Reports and Analytics");
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}
