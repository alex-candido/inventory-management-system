#include <gtk/gtk.h>
#include "product.h"
#include "stock.h"
#include "layout.h"

static GtkWidget *content_box;

static void destroy_widget_wrapper(gpointer widget, gpointer user_data)
{
    (void)user_data;
    gtk_widget_destroy(GTK_WIDGET(widget));
}

static void clear_content()
{
    GList *children = gtk_container_get_children(GTK_CONTAINER(content_box));
    g_list_foreach(children, (GFunc)destroy_widget_wrapper, NULL); //

    g_list_free(children);
}

static void on_nav_button_clicked(GtkButton *button, gpointer user_data)
{
    (void)button;
    const char *view_name = (const char *)user_data;

    clear_content();

    GtkWidget *view = NULL;
    if (strcmp(view_name, "dashboard") == 0)
    {
        view = create_dashboard_view();
    }
    else if (strcmp(view_name, "products") == 0)
    {
        view = create_product_list_view();
    }
    else if (strcmp(view_name, "stock") == 0)
    {
        view = create_stock_list_view();
    }
    else if (strcmp(view_name, "reports") == 0)
    {
        view = create_reports_view();
    }

    if (view)
    {
        gtk_container_add(GTK_CONTAINER(content_box), view);
        gtk_widget_show_all(content_box);
    }
}

static GtkWidget *create_nav_button(const char *label, const char *view_name)
{
    GtkWidget *button = gtk_button_new_with_label(label);
    gtk_widget_set_size_request(button, -1, 40);
    g_signal_connect(button, "clicked", G_CALLBACK(on_nav_button_clicked), (gpointer)view_name);
    return button;
}

GtkWidget *create_main_layout()
{
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    // Sidebar
    GtkWidget *sidebar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_size_request(sidebar, 200, -1);
    gtk_widget_set_margin_start(sidebar, 10);
    gtk_widget_set_margin_end(sidebar, 10);
    gtk_widget_set_margin_top(sidebar, 10);
    gtk_widget_set_margin_bottom(sidebar, 10);

    // Navigation buttons
    GtkWidget *dashboard_btn = create_nav_button("Dashboard", "dashboard");
    GtkWidget *products_btn = create_nav_button("Products", "products");
    GtkWidget *stock_btn = create_nav_button("Stock", "stock");
    GtkWidget *reports_btn = create_nav_button("Reports", "reports");

    gtk_box_pack_start(GTK_BOX(sidebar), dashboard_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(sidebar), products_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(sidebar), stock_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(sidebar), reports_btn, FALSE, FALSE, 0);

    // Content area
    content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Add sidebar and content to main box
    gtk_box_pack_start(GTK_BOX(main_box), sidebar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), content_box, TRUE, TRUE, 0);

    // Show dashboard by default
    on_nav_button_clicked(NULL, "dashboard");

    return main_box;
}