#include <gtk/gtk.h>
#include "views/product/edit_view.h"

// Função para exibir a edição de produtos
void show_product_edit(GtkWidget *content_area, Product *product)
{
  // ... (Implementação da tela de edição - use content_area e product)
  GList *children = gtk_container_get_children(GTK_CONTAINER(content_area));
  for (GList *iter = children; iter != NULL; iter = g_list_next(iter))
  {
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  }
  g_list_free(children);

  GtkWidget *label = gtk_label_new(product->name);
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}
