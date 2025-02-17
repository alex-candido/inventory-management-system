#include <gtk/gtk.h>
#include "../../include/views/stock/index_view.h"
#include "views/stock/show_view.h"
#include "views/stock/new_view.h"
#include "views/stock/edit_view.h"

// Função para exibir o índice de estoque
void show_stock_index(GtkWidget *content_area)
{
  GtkWidget *label = gtk_label_new("Stock Index");
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}

// Outras funções para acessar views de estoque
void show_stock_show(GtkWidget *content_area)
{
  GtkWidget *label = gtk_label_new("Stock Show");
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}

void show_stock_new(GtkWidget *content_area)
{
  GtkWidget *label = gtk_label_new("Stock New");
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}

void show_stock_edit(GtkWidget *content_area)
{
  GtkWidget *label = gtk_label_new("Stock Edit");
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}
