#include <gtk/gtk.h>
#include <stdio.h>
#include "views/layouts/main_layout.h"

// Função de inicialização da aplicação
static void app_init(GtkApplication *app)
{
  GtkWidget *window;

  // Cria a janela principal
  window = gtk_application_window_new(app);

  gtk_window_set_title(GTK_WINDOW(window), "Inventory Management");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

  // Cria o layout padrão
  create_main_layout(window);

  // Exibe a janela
  gtk_widget_show_all(window);
}
// Função principal
int main(int argc, char *argv[])
{
  GtkApplication *app;
  int status;

  // Inicializa o GTK
  app = gtk_application_new("com.example.InventoryApp", G_APPLICATION_DEFAULT_FLAGS);
  // Conecta a função de inicialização
  g_signal_connect(app, "activate", G_CALLBACK(app_init), NULL);

  // Executa a aplicação
  status = g_application_run(G_APPLICATION(app), argc, argv);

  g_object_unref(app);
  return status;
}
