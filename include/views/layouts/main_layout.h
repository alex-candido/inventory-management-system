#ifndef MAIN_LAYOUT_H
#define MAIN_LAYOUT_H

#include <gtk/gtk.h>

// Declarações de funções de callback
void on_dashboard_clicked(GtkWidget *widget, gpointer data);
void on_manage_products_clicked(GtkWidget *widget, gpointer data);
void on_manage_stocks_clicked(GtkWidget *widget, gpointer data);
void on_exit_button_clicked(GtkWidget *widget, gpointer data);
void on_window_destroy(GtkWidget *widget, gpointer data);

// Declaração das funções para carregar as views
void load_product_index_view(GtkWidget *content_area);
void load_stock_index_view(GtkWidget *content_area);

// Declaração da função para criar o layout principal
GtkWidget *create_main_layout(GtkWidget *window);

#endif // MAIN_LAYOUT_H
