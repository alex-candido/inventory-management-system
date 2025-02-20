#include <gtk/gtk.h>
#include "views/layouts/main_layout.h"
#include "views/dashboard/index_view.h"
#include "views/product/index_view.h"
#include "views/stock/index_view.h"

// Função auxiliar para criar botões do menu
static GtkWidget *create_menu_button(const char *label_text, const char *icon_name)
{
  GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  GtkWidget *button = gtk_button_new();
  GtkWidget *icon = gtk_image_new_from_icon_name(icon_name, GTK_ICON_SIZE_DIALOG);
  gtk_image_set_pixel_size(GTK_IMAGE(icon), 24);

  GtkWidget *label = gtk_label_new(label_text);

  gtk_container_add(GTK_CONTAINER(button_box), icon);
  gtk_container_add(GTK_CONTAINER(button_box), label);
  gtk_container_add(GTK_CONTAINER(button), button_box);

  gtk_widget_set_halign(button, GTK_ALIGN_FILL);
  gtk_widget_set_size_request(button, 200, 40);

  return button;
}

// Função para criar o layout padrão
GtkWidget *create_main_layout(GtkWidget *window)
{
  GtkWidget *main_box;
  GtkWidget *header_bar;
  GtkWidget *sidebar;
  GtkWidget *content_area;
  GtkCssProvider *provider;

  // Configurar CSS para estilização
  provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "assets/css/style.css", NULL);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(provider),
                                            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  // Criar header bar
  header_bar = gtk_header_bar_new();
  gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Admin System");
  gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header_bar), "Inventory Management");
  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
  gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);

  // Criar layout principal
  main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add(GTK_CONTAINER(window), main_box);

  // Criar sidebar
  sidebar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_style_context_add_class(gtk_widget_get_style_context(sidebar), "sidebar");
  gtk_widget_set_size_request(sidebar, 250, -1); // 25% da largura da tela

  // Criar área de conteúdo
  content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_style_context_add_class(gtk_widget_get_style_context(content_area), "content-area");

  // Criar título da sidebar
  GtkWidget *title_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  GtkWidget *title_label = gtk_label_new("Admin System");

  gtk_style_context_add_class(gtk_widget_get_style_context(title_label), "app-title");

  gtk_box_pack_start(GTK_BOX(title_box), title_label, FALSE, FALSE, 0);

  // Criar separador
  GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_widget_set_margin_top(separator, 10);
  gtk_widget_set_margin_bottom(separator, 10);

  // Criar botões do menu
  GtkWidget *dashboard_button = create_menu_button("Dashboard", "view-grid-symbolic");
  GtkWidget *products_button = create_menu_button("Produtos", "package-symbolic");
  GtkWidget *stocks_button = create_menu_button("Estoque", "view-list-symbolic");
  GtkWidget *exit_button = create_menu_button("Sair", "system-shutdown-symbolic");

  // Adicionar classes CSS aos botões
  gtk_style_context_add_class(gtk_widget_get_style_context(dashboard_button), "menu-button");
  gtk_style_context_add_class(gtk_widget_get_style_context(products_button), "menu-button");
  gtk_style_context_add_class(gtk_widget_get_style_context(stocks_button), "menu-button");
  gtk_style_context_add_class(gtk_widget_get_style_context(exit_button), "menu-button");

  // Montar a sidebar
  gtk_box_pack_start(GTK_BOX(sidebar), title_box, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(sidebar), separator, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(sidebar), dashboard_button, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(sidebar), products_button, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(sidebar), stocks_button, FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(sidebar), exit_button, FALSE, FALSE, 0);

  // Adicionar sidebar e content_area ao container principal
  gtk_box_pack_start(GTK_BOX(main_box), sidebar, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(main_box), content_area, TRUE, TRUE, 0);

  // Conectar sinais
  g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);
  g_signal_connect(dashboard_button, "clicked", G_CALLBACK(on_dashboard_clicked), content_area);
  g_signal_connect(products_button, "clicked", G_CALLBACK(on_manage_products_clicked), content_area);
  g_signal_connect(stocks_button, "clicked", G_CALLBACK(on_manage_stocks_clicked), content_area);
  g_signal_connect(exit_button, "clicked", G_CALLBACK(on_exit_button_clicked), window);

  // Mostrar dashboard inicial
  show_dashboard(content_area);

  g_object_unref(provider);

  return main_box;
}

// As funções de callback permanecem as mesmas
void on_window_destroy(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;
  gtk_main_quit();
}

void on_exit_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)data;
  GtkWidget *window = gtk_widget_get_toplevel(widget);
  gtk_widget_destroy(window);
}

void on_dashboard_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  GtkWidget *content_area = (GtkWidget *)data;
  show_dashboard(content_area);
}

void on_manage_products_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  GtkWidget *content_area = (GtkWidget *)data;
  show_product_index(content_area);
}

void on_manage_stocks_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  GtkWidget *content_area = (GtkWidget *)data;
  show_stock_index(content_area);
}
