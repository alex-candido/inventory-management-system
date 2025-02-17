#include <gtk/gtk.h>
#include "views/layouts/main_layout.h"
#include "views/dashboard/index_view.h"
#include "views/product/index_view.h"
#include "views/stock/index_view.h"

// Função para criar o layout padrão
GtkWidget *create_main_layout(GtkWidget *window)
{
  GtkBuilder *builder;
  GtkWidget *main_box;
  GtkWidget *manage_products_button, *manage_stocks_button, *exit_button, *content_area, *dashboard_button;

  // Carregar o layout a partir do arquivo .glade
  builder = gtk_builder_new_from_file("views/layouts/main_layout.glade");

  main_box = GTK_WIDGET(gtk_builder_get_object(builder, "main_box"));
  content_area = GTK_WIDGET(gtk_builder_get_object(builder, "content_area"));

  // Obtenha os botões
  dashboard_button = GTK_WIDGET(gtk_builder_get_object(builder, "dashboard_button"));
  manage_products_button = GTK_WIDGET(gtk_builder_get_object(builder, "manage_products_button"));
  manage_stocks_button = GTK_WIDGET(gtk_builder_get_object(builder, "manage_stocks_button"));
  exit_button = GTK_WIDGET(gtk_builder_get_object(builder, "exit_button"));

  // Remove o main_box do container anterior, se necessário
  if (gtk_widget_get_parent(main_box) != NULL)
  {
    gtk_widget_unparent(main_box);
  }

  // Adiciona main_box ao container da window
  gtk_container_add(GTK_CONTAINER(window), main_box);

  // Conecta sinais aos botões
  g_signal_connect(dashboard_button, "clicked", G_CALLBACK(on_dashboard_clicked), content_area);
  g_signal_connect(manage_products_button, "clicked", G_CALLBACK(on_manage_products_clicked), content_area);
  g_signal_connect(manage_stocks_button, "clicked", G_CALLBACK(on_manage_stocks_clicked), content_area);
  g_signal_connect(exit_button, "clicked", G_CALLBACK(on_exit_button_clicked), window);

  show_dashboard(content_area);

  return main_box;
}

// Função para lidar com o evento de destruição da janela
void on_window_destroy(GtkWidget *widget, gpointer data)
{
  (void)widget;    // Desativa o aviso de parâmetro não utilizado
  (void)data;      // Desativa o aviso de parâmetro não utilizado
  gtk_main_quit(); // Fecha a aplicação
}

void on_exit_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget; // Desativa o aviso de parâmetro não utilizado
  (void)data;   // Desativa o aviso de parâmetro não utilizado
  GtkWidget *window = gtk_widget_get_toplevel(widget);
  gtk_widget_destroy(window);
}

void on_dashboard_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget; // Desativa o aviso de parâmetro não utilizado
  GtkWidget *content_area = (GtkWidget *)data;
  show_dashboard(content_area);
}

void on_manage_products_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget; // Desativa o aviso de parâmetro não utilizado
  GtkWidget *content_area = (GtkWidget *)data;
  load_product_index_view(content_area);
}

void on_manage_stocks_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget; // Desativa o aviso de parâmetro não utilizado
  GtkWidget *content_area = (GtkWidget *)data;
  load_stock_index_view(content_area);
}

// Função para carregar a view de gerenciamento de produtos
void load_product_index_view(GtkWidget *content_area)
{
  // Remover todos os widgets filhos do content_area antes de adicionar novos
  GList *children, *iter;
  children = gtk_container_get_children(GTK_CONTAINER(content_area));
  for (iter = children; iter != NULL; iter = g_list_next(iter))
  {
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  }
  g_list_free(children);

  // Adicionar novo conteúdo ao content_area
  show_product_index(content_area);
}

// Função para carregar a view de gerenciamento de estoque
void load_stock_index_view(GtkWidget *content_area)
{
  // Remover todos os widgets filhos do content_area antes de adicionar novos
  GList *children, *iter;
  children = gtk_container_get_children(GTK_CONTAINER(content_area));
  for (iter = children; iter != NULL; iter = g_list_next(iter))
  {
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  }
  g_list_free(children);

  show_stock_index(content_area);
}
