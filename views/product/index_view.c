#include <gtk/gtk.h>
#include "../../include/views/product/index_view.h"
#include "views/product/show_view.h"
#include "views/product/new_view.h"
#include "views/product/edit_view.h"

// Função para exibir o índice de produtos
void show_product_index(GtkWidget *content_area)
{
  GtkWidget *label = gtk_label_new("Product Index");
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}

// Outras funções para acessar views de produtos
void show_product_show(GtkWidget *content_area)
{
  GtkWidget *label = gtk_label_new("Product Show");
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}

void show_product_new(GtkWidget *content_area)
{
  GtkWidget *label = gtk_label_new("Product New");
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}

void show_product_edit(GtkWidget *content_area)
{
  GtkWidget *label = gtk_label_new("Product Edit");
  gtk_container_add(GTK_CONTAINER(content_area), label);
  gtk_widget_show_all(content_area);
}
