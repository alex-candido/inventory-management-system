#include <gtk/gtk.h>

#include "views/product/index_view.h"
#include "views/product/edit_view.h"
#include "views/product/new_view.h"
#include "views/product/show_view.h"

#include "services/product/read_product_service.h"

typedef struct
{
  GtkWidget *content_area;
  Product *product;
} CallbackData;

#define PRODUCTS_PER_PAGE 5

// Declarações de Funções (Protótipos)
void on_prev_button_clicked(GtkWidget *widget, gpointer data);
void on_next_button_clicked(GtkWidget *widget, gpointer data);
void on_edit_clicked(GtkWidget *widget, gpointer data);
void on_show_clicked(GtkWidget *widget, gpointer data);
void on_new_clicked(GtkWidget *widget, gpointer data);

// Variáveis para controle da página atual
static int current_page = 1;
static int total_products = 0;

// Função auxiliar para carregar CSS
static void load_css()
{
  GtkCssProvider *provider = gtk_css_provider_new();
  GError *error = NULL;

  if (!gtk_css_provider_load_from_path(provider, "assets/css/style.css", &error))
  {
    g_warning("Erro ao carregar CSS: %s", error->message);
    g_error_free(error);
  }

  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(provider),
                                            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  g_object_unref(provider);
}

void show_product_index(GtkWidget *content_area)
{
  // Remove os widgets anteriores
  GList *children = gtk_container_get_children(GTK_CONTAINER(content_area));
  for (GList *iter = children; iter != NULL; iter = g_list_next(iter))
  {
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  }
  g_list_free(children);

  // Carregar o CSS para estilização
  load_css();

  // Hero Section
  GtkWidget *title_label = gtk_label_new("Products");
  GtkWidget *leading_label = gtk_label_new("List Products, Edit and More");

  gtk_style_context_add_class(gtk_widget_get_style_context(title_label), "hero-title");
  gtk_style_context_add_class(gtk_widget_get_style_context(leading_label), "hero-subtitle");

  GtkWidget *hero_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5); // Caixa horizontal principal
  gtk_style_context_add_class(gtk_widget_get_style_context(hero_box), "hero-section");

  // Caixa vertical para título e subtítulo (agora é *dentro* da hero_box)
  GtkWidget *hero_left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Espaçamento 0
  gtk_box_pack_start(GTK_BOX(hero_left_box), title_label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hero_left_box), leading_label, FALSE, FALSE, 0);

  // Botão "New" (agora é *diretamente* adicionado à hero_box)
  GtkWidget *new_button = gtk_button_new_with_label("New");
  gtk_style_context_add_class(gtk_widget_get_style_context(new_button), "table-action-button");
  g_signal_connect(new_button, "clicked", G_CALLBACK(on_new_clicked), content_area);

  // Adiciona a caixa vertical (título/subtítulo) à hero_box
  gtk_box_pack_start(GTK_BOX(hero_box), hero_left_box, TRUE, TRUE, 0); // Expande horizontalmente

  // Adiciona o botão "New" à hero_box (alinhado à direita)
  GtkWidget *new_button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0); // Caixa para alinhar o botão
  gtk_box_pack_start(GTK_BOX(new_button_box), new_button, FALSE, FALSE, 0);
  gtk_widget_set_halign(new_button_box, GTK_ALIGN_END);
  gtk_box_pack_start(GTK_BOX(hero_box), new_button_box, FALSE, FALSE, 0);

  // Tabela como Card
  GtkWidget *table = gtk_grid_new();
  gtk_grid_set_row_homogeneous(GTK_GRID(table), TRUE);
  gtk_grid_set_column_homogeneous(GTK_GRID(table), TRUE);
  gtk_style_context_add_class(gtk_widget_get_style_context(table), "product-card");

  // Cabeçalhos da Tabela
  GtkWidget *id_label = gtk_label_new("Id");
  GtkWidget *name_label = gtk_label_new("Name");
  GtkWidget *category_label = gtk_label_new("Category");
  GtkWidget *price_label = gtk_label_new("Price");
  GtkWidget *description_label = gtk_label_new("Description"); // Novo cabeçalho para descrição
  GtkWidget *quantity_label = gtk_label_new("Quantity");       // Novo cabeçalho para quantidade
  GtkWidget *status_label = gtk_label_new("Status");           // Novo cabeçalho para status
  GtkWidget *actions_label = gtk_label_new("Actions");         // Novo cabeçalho para ações

  gtk_style_context_add_class(gtk_widget_get_style_context(id_label), "table-header");
  gtk_style_context_add_class(gtk_widget_get_style_context(name_label), "table-header");
  gtk_style_context_add_class(gtk_widget_get_style_context(category_label), "table-header");
  gtk_style_context_add_class(gtk_widget_get_style_context(price_label), "table-header");
  gtk_style_context_add_class(gtk_widget_get_style_context(description_label), "table-header");
  gtk_style_context_add_class(gtk_widget_get_style_context(quantity_label), "table-header");
  gtk_style_context_add_class(gtk_widget_get_style_context(status_label), "table-header");
  gtk_style_context_add_class(gtk_widget_get_style_context(actions_label), "table-header");

  gtk_grid_attach(GTK_GRID(table), id_label, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(table), name_label, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(table), category_label, 2, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(table), price_label, 3, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(table), description_label, 4, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(table), quantity_label, 5, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(table), status_label, 6, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(table), actions_label, 7, 0, 1, 1); // Adiciona o cabeçalho das ações na coluna 9

  // Obtém o número total de produtos
  total_products = get_total_products();

  // Lê os produtos da página atual
  int num_products = 0;
  Product *products = read_products(current_page, &num_products);

  if (products != NULL)
  {
    for (int i = 0; i < num_products; i++)
    {
      // Para cada produto, cria widgets de texto e os adiciona à tabela
      GtkWidget *id_data = gtk_label_new(g_strdup_printf("%d", products[i].id));
      GtkWidget *name_data = gtk_label_new(products[i].name);
      GtkWidget *category_data = gtk_label_new(products[i].category);
      GtkWidget *price_data = gtk_label_new(g_strdup_printf("R$ %.2f", products[i].price));
      GtkWidget *description_data = gtk_label_new(products[i].description);
      GtkWidget *quantity_data = gtk_label_new(g_strdup_printf("%d", products[i].quantity));
      GtkWidget *status_data = gtk_label_new(products[i].status == 1 ? "Ativo" : "Inativo");

      gtk_style_context_add_class(gtk_widget_get_style_context(id_data), "table-data");
      gtk_style_context_add_class(gtk_widget_get_style_context(name_data), "table-data");
      gtk_style_context_add_class(gtk_widget_get_style_context(category_data), "table-data");
      gtk_style_context_add_class(gtk_widget_get_style_context(price_data), "table-data");
      gtk_style_context_add_class(gtk_widget_get_style_context(description_data), "table-data");
      gtk_style_context_add_class(gtk_widget_get_style_context(quantity_data), "table-data");
      gtk_style_context_add_class(gtk_widget_get_style_context(status_data), "table-data");

      // Alinha o conteúdo ao centro de cada coluna
      gtk_widget_set_halign(id_data, GTK_ALIGN_CENTER);
      gtk_widget_set_halign(name_data, GTK_ALIGN_CENTER);
      gtk_widget_set_halign(category_data, GTK_ALIGN_CENTER);
      gtk_widget_set_halign(price_data, GTK_ALIGN_CENTER);
      gtk_widget_set_halign(description_data, GTK_ALIGN_CENTER);
      gtk_widget_set_halign(quantity_data, GTK_ALIGN_CENTER);
      gtk_widget_set_halign(status_data, GTK_ALIGN_CENTER);

      // Defina o comportamento das colunas
      gtk_grid_attach(GTK_GRID(table), id_data, 0, i + 1, 1, 1);
      gtk_grid_attach(GTK_GRID(table), name_data, 1, i + 1, 1, 1);
      gtk_grid_attach(GTK_GRID(table), category_data, 2, i + 1, 1, 1);
      gtk_grid_attach(GTK_GRID(table), price_data, 3, i + 1, 1, 1);
      gtk_grid_attach(GTK_GRID(table), description_data, 4, i + 1, 1, 1);
      gtk_grid_attach(GTK_GRID(table), quantity_data, 5, i + 1, 1, 1);
      gtk_grid_attach(GTK_GRID(table), status_data, 6, i + 1, 1, 1);

      // Criação dos botões de ação
      GtkWidget *edit_button = gtk_button_new_with_label("Edit");
      GtkWidget *show_button = gtk_button_new_with_label("Show");

      gtk_style_context_add_class(gtk_widget_get_style_context(edit_button), "table-action-button");
      gtk_style_context_add_class(gtk_widget_get_style_context(show_button), "table-action-button");

      CallbackData *edit_callback_data = g_new(CallbackData, 1);
      edit_callback_data->content_area = content_area;
      edit_callback_data->product = &products[i];

      CallbackData *show_callback_data = g_new(CallbackData, 1);
      show_callback_data->content_area = content_area;
      show_callback_data->product = &products[i];

      g_signal_connect(edit_button, "clicked", G_CALLBACK(on_edit_clicked), edit_callback_data);
      g_signal_connect(show_button, "clicked", G_CALLBACK(on_show_clicked), show_callback_data);

      // Cria um box para conter os botões de ação e centralizá-los
      GtkWidget *actions_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5); // Espaçamento de 5 pixels
      gtk_box_pack_start(GTK_BOX(actions_box), show_button, FALSE, FALSE, 0);
      gtk_box_pack_start(GTK_BOX(actions_box), edit_button, FALSE, FALSE, 0);
      gtk_widget_set_halign(actions_box, GTK_ALIGN_CENTER); // Centraliza os botões

      gtk_grid_attach(GTK_GRID(table), actions_box, 7, i + 1, 1, 1); // Adiciona o box de ações na coluna 6
    }

    // Libera a memória dos produtos
    free(products);
  }

  // Calcular o número total de páginas
  int total_pages = (total_products + PRODUCTS_PER_PAGE - 1) / PRODUCTS_PER_PAGE;

  // Paginação
  GtkWidget *prev_button = gtk_button_new_with_label("Previous");
  GtkWidget *next_button = gtk_button_new_with_label("Next");
  gtk_style_context_add_class(gtk_widget_get_style_context(prev_button), "navigation-button");
  gtk_style_context_add_class(gtk_widget_get_style_context(next_button), "navigation-button");

  // Desabilita o botão "Previous" se já estiver na primeira página
  if (current_page == 1)
  {
    gtk_widget_set_sensitive(prev_button, FALSE);
  }
  else
  {
    gtk_widget_set_sensitive(prev_button, TRUE);
  }

  // Desabilita o botão "Next" se já estiver na última página
  if (current_page == total_pages)
  {
    gtk_widget_set_sensitive(next_button, FALSE);
  }
  else
  {
    gtk_widget_set_sensitive(next_button, TRUE);
  }

  // Conecta os sinais dos botões às funções de callback
  g_signal_connect(prev_button, "clicked", G_CALLBACK(on_prev_button_clicked), content_area);
  g_signal_connect(next_button, "clicked", G_CALLBACK(on_next_button_clicked), content_area);

  GtkWidget *navigation_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_box_pack_start(GTK_BOX(navigation_box), prev_button, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(navigation_box), next_button, TRUE, TRUE, 0);

  // Layout principal
  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20); // Espaçamento entre as seções

  gtk_box_pack_start(GTK_BOX(main_box), hero_box, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(main_box), table, TRUE, TRUE, 0); // A tabela que agora funciona como o card
  gtk_box_pack_start(GTK_BOX(main_box), navigation_box, FALSE, FALSE, 0);

  gtk_container_add(GTK_CONTAINER(content_area), main_box);
  gtk_widget_show_all(content_area);
}

void on_prev_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  GtkWidget *content_area = (GtkWidget *)data;
  if (current_page > 1)
  {
    current_page--;
  }
  show_product_index(content_area);
}

void on_next_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  GtkWidget *content_area = (GtkWidget *)data;
  total_products = get_total_products();
  int total_pages = (total_products + PRODUCTS_PER_PAGE - 1) / PRODUCTS_PER_PAGE;

  if (current_page < total_pages)
  {
    current_page++;
  }

  show_product_index(content_area);
}

void on_edit_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  CallbackData *callback_data = (CallbackData *)data;

  if (callback_data && callback_data->product)
  {
    Product *product = callback_data->product;
    GtkWidget *content_area = callback_data->content_area;
    g_print("Edit clicked for product ID: %d, Name: %s\n", product->id, product->name);

    show_product_edit(content_area, product); // Ordem corrigida dos parâmetros
  }
  else
  {
    g_print("Invalid product data for edit.\n");
  }
  g_free(callback_data); // Libera a memória alocada para os dados de callback
}

void on_show_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  CallbackData *callback_data = (CallbackData *)data;

  if (callback_data && callback_data->product)
  {
    Product *product = callback_data->product;
    GtkWidget *content_area = callback_data->content_area;
    g_print("Show clicked for product ID: %d, Name: %s\n", product->id, product->name);

    show_product_show(content_area, product); // Ordem corrigida dos parâmetros
  }
  else
  {
    g_print("Invalid product data for show.\n");
  }
  g_free(callback_data); // Libera a memória alocada para os dados de callback
}

void on_new_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  GtkWidget *content_area = (GtkWidget *)data;

  // Chama a função para mostrar a tela de novo produto
  show_product_new(content_area); // Passando o parâmetro necessário
}
