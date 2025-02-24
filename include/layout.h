#ifndef LAYOUT_H
#define LAYOUT_H

#include <gtk/gtk.h>

// Função para criar o layout principal da aplicação
GtkWidget *create_main_layout();
GtkWidget *create_dashboard_view(void);
GtkWidget *create_product_list_view(void);
GtkWidget *create_stock_list_view(void);
GtkWidget *create_reports_view(void);

#endif // LAYOUT_H
