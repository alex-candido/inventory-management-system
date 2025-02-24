#include <gtk/gtk.h>
#include <string.h>

#include "product.h"
#include "layout.h"
#include "stock.h"
#include "utils.h"

static void activate(GtkApplication *app)
{
  GtkWidget *window;
  GtkWidget *header;
  GtkWidget *main_box;

  // Create the main window
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Sistema de Gerenciamento de Inventário");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

  // Create header bar
  header = gtk_header_bar_new();
  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
  gtk_header_bar_set_title(GTK_HEADER_BAR(header), "inventory management");
  gtk_window_set_titlebar(GTK_WINDOW(window), header);

  // Create main layout
  main_box = create_main_layout();
  gtk_container_add(GTK_CONTAINER(window), main_box);

  // Show all widgets
  gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
  // Check for --seed argument
  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "--seed") == 0)
    {
      // Initialize services before seeding
      init_products();
      init_stock();

      // Run seeding process
      seed_products();
      seed_stocks();

      return 0;
    }
  }

  GtkApplication *app;
  int status;

  // Initialize product and stock services
  init_products();
  init_stock();

  app = gtk_application_new("com.example.stock-sys", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
