#include <gtk/gtk.h>
#include "report.h"

static GtkWidget *content_box;
static GtkWidget *out_of_stock_view;
static GtkWidget *location_view;
static GtkWidget *recent_products_view;
static GtkWidget *category_view;
static GtkWidget *valuation_view;

// Helper function to create a label with specific style
static GtkWidget *create_styled_label(const char *text, gboolean is_bold, double scale)
{
  GtkWidget *label = gtk_label_new(text);
  PangoAttrList *attr_list = pango_attr_list_new();

  if (is_bold)
  {
    pango_attr_list_insert(attr_list, pango_attr_weight_new(PANGO_WEIGHT_BOLD));
  }
  if (scale > 0.0)
  {
    pango_attr_list_insert(attr_list, pango_attr_scale_new(scale));
  }

  gtk_label_set_attributes(GTK_LABEL(label), attr_list);
  pango_attr_list_unref(attr_list);
  return label;
}

// Helper function to create a section container
static GtkWidget *create_section(const char *title)
{
  // Create a container for the entire section
  GtkWidget *section_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_widget_set_margin_start(section_container, 10);
  gtk_widget_set_margin_end(section_container, 10);
  gtk_widget_set_margin_top(section_container, 10);
  gtk_widget_set_margin_bottom(section_container, 10);

  // Create and style the title label
  GtkWidget *title_label = create_styled_label(title, TRUE, 1.2);
  gtk_label_set_xalign(GTK_LABEL(title_label), 0.0);
  gtk_label_set_line_wrap(GTK_LABEL(title_label), TRUE);
  gtk_label_set_line_wrap_mode(GTK_LABEL(title_label), PANGO_WRAP_WORD);
  gtk_widget_set_margin_start(title_label, 5);
  gtk_widget_set_margin_bottom(title_label, 10);

  // Create the frame for content
  GtkWidget *frame = gtk_frame_new(NULL);

  // Create the content box
  GtkWidget *content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_add(GTK_CONTAINER(frame), content_box);

  // Pack everything into the section container
  gtk_box_pack_start(GTK_BOX(section_container), title_label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(section_container), frame, TRUE, TRUE, 0);

  return section_container;
}

// Update Out of Stock Products view
static void update_out_of_stock_view()
{
  GList *report = report_out_of_stock_products(5); // Minimum quantity threshold

  GtkWidget *list_box = gtk_list_box_new();
  gtk_list_box_set_selection_mode(GTK_LIST_BOX(list_box), GTK_SELECTION_NONE);

  for (GList *item = report; item != NULL; item = item->next)
  {
    ReportOutOfStock *product = item->data;

    GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_start(row, 5);
    gtk_widget_set_margin_end(row, 5);
    gtk_widget_set_margin_top(row, 5);
    gtk_widget_set_margin_bottom(row, 5);

    char qty_str[32];
    snprintf(qty_str, sizeof(qty_str), "%d", product->quantity);

    gtk_box_pack_start(GTK_BOX(row), gtk_label_new(product->product_name), TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(row), gtk_label_new(product->category), TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(row), gtk_label_new(qty_str), TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(row), gtk_label_new(product->updated_at), TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(list_box), row);
  }

  gtk_container_add(GTK_CONTAINER(out_of_stock_view), list_box);
  gtk_widget_show_all(out_of_stock_view);

  report_free_out_of_stock(report);
}

// Update Products by Location view
static void update_location_view()
{
  GList *report = report_products_by_location();

  GtkWidget *list_box = gtk_list_box_new();
  gtk_list_box_set_selection_mode(GTK_LIST_BOX(list_box), GTK_SELECTION_NONE);

  for (GList *loc_item = report; loc_item != NULL; loc_item = loc_item->next)
  {
    ReportLocation *location = loc_item->data;

    // Location header
    GtkWidget *location_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *location_label = create_styled_label(location->location, TRUE, 1.0);
    gtk_box_pack_start(GTK_BOX(location_box), location_label, FALSE, FALSE, 5);

    // Add headers for products
    GtkWidget *product_list_header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_start(product_list_header, 20);

    GtkWidget *prod_name_header = create_styled_label("Product Name", TRUE, 1.0);
    GtkWidget *prod_qty_header = create_styled_label("Quantity", TRUE, 1.0);

    gtk_box_pack_start(GTK_BOX(product_list_header), prod_name_header, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(product_list_header), prod_qty_header, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(location_box), product_list_header, FALSE, FALSE, 5);

    // Products in this location
    for (GList *prod_item = location->products; prod_item != NULL; prod_item = prod_item->next)
    {
      ReportLocationProduct *product = prod_item->data;

      GtkWidget *product_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
      gtk_widget_set_margin_start(product_box, 20);

      char qty_str[32];
      snprintf(qty_str, sizeof(qty_str), "%d", product->quantity);

      gtk_box_pack_start(GTK_BOX(product_box), gtk_label_new(product->product_name), TRUE, TRUE, 0);
      gtk_box_pack_start(GTK_BOX(product_box), gtk_label_new(qty_str), FALSE, FALSE, 0);

      gtk_box_pack_start(GTK_BOX(location_box), product_box, FALSE, FALSE, 0);
    }

    gtk_container_add(GTK_CONTAINER(list_box), location_box);
  }

  gtk_container_add(GTK_CONTAINER(location_view), list_box);
  gtk_widget_show_all(location_view);

  report_free_location(report);
}

// Update Recent Products view
static void update_recent_products_view()
{
  GList *report = report_recent_products();

  GtkWidget *list_box = gtk_list_box_new();
  gtk_list_box_set_selection_mode(GTK_LIST_BOX(list_box), GTK_SELECTION_NONE);

  // Add headers
  GtkWidget *header_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_widget_set_margin_start(header_row, 5);
  gtk_widget_set_margin_end(header_row, 5);
  gtk_widget_set_margin_top(header_row, 5);
  gtk_widget_set_margin_bottom(header_row, 5);

  GtkWidget *name_header = create_styled_label("Product Name", TRUE, 1.0);
  GtkWidget *category_header = create_styled_label("Category", TRUE, 1.0);
  GtkWidget *date_header = create_styled_label("Created At", TRUE, 1.0);

  gtk_box_pack_start(GTK_BOX(header_row), name_header, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(header_row), category_header, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(header_row), date_header, TRUE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER(list_box), header_row);

  for (GList *item = report; item != NULL; item = item->next)
  {
    ReportRecentProduct *product = item->data;

    GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_start(row, 5);
    gtk_widget_set_margin_end(row, 5);
    gtk_widget_set_margin_top(row, 5);
    gtk_widget_set_margin_bottom(row, 5);

    gtk_box_pack_start(GTK_BOX(row), gtk_label_new(product->name), TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(row), gtk_label_new(product->category), TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(row), gtk_label_new(product->created_at), TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(list_box), row);
  }

  gtk_container_add(GTK_CONTAINER(recent_products_view), list_box);
  gtk_widget_show_all(recent_products_view);

  report_free_recent_products(report);
}

// Update Products by Category view
static void update_category_view()
{
  GList *report = report_products_by_category();

  GtkWidget *list_box = gtk_list_box_new();
  gtk_list_box_set_selection_mode(GTK_LIST_BOX(list_box), GTK_SELECTION_NONE);

  // Add headers
  GtkWidget *header_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_widget_set_margin_start(header_row, 5);
  gtk_widget_set_margin_end(header_row, 5);
  gtk_widget_set_margin_top(header_row, 5);
  gtk_widget_set_margin_bottom(header_row, 5);

  GtkWidget *category_header = create_styled_label("Category", TRUE, 1.0);
  GtkWidget *quantity_header = create_styled_label("Total Quantity", TRUE, 1.0);
  GtkWidget *total_price_header = create_styled_label("Total Value", TRUE, 1.0);
  GtkWidget *avg_price_header = create_styled_label("Average Value", TRUE, 1.0);
  GtkWidget *count_header = create_styled_label("Product Count", TRUE, 1.0);

  gtk_box_pack_start(GTK_BOX(header_row), category_header, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(header_row), quantity_header, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(header_row), total_price_header, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(header_row), avg_price_header, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(header_row), count_header, TRUE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER(list_box), header_row);

  for (GList *item = report; item != NULL; item = item->next)
  {
    ReportCategory *category = item->data;

    GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_start(row, 5);
    gtk_widget_set_margin_end(row, 5);
    gtk_widget_set_margin_top(row, 5);
    gtk_widget_set_margin_bottom(row, 5);

    char qty_str[32], price_str[32], avg_str[32], count_str[32];
    snprintf(qty_str, sizeof(qty_str), "%d", category->total_quantity);
    snprintf(price_str, sizeof(price_str), "R$ %.2f", category->total_price);
    snprintf(avg_str, sizeof(avg_str), "R$ %.2f", category->avg_price);
    snprintf(count_str, sizeof(count_str), "%d", category->product_count);

    gtk_box_pack_start(GTK_BOX(row), gtk_label_new(category->category), TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(row), gtk_label_new(qty_str), TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(row), gtk_label_new(price_str), TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(row), gtk_label_new(avg_str), TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(row), gtk_label_new(count_str), TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(list_box), row);
  }

  gtk_container_add(GTK_CONTAINER(category_view), list_box);
  gtk_widget_show_all(category_view);

  report_free_category(report);
}

// Update Stock Valuation view
static void update_valuation_view()
{
  ReportValuation *report = report_stock_valuation();

  GtkWidget *info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_margin_start(info_box, 20);
  gtk_widget_set_margin_end(info_box, 20);
  gtk_widget_set_margin_top(info_box, 10);
  gtk_widget_set_margin_bottom(info_box, 10);

  char value_str[64], items_str[32];
  snprintf(value_str, sizeof(value_str), "Total Value: R$ %.2f", report->total_value);
  snprintf(items_str, sizeof(items_str), "Total Items: %d", report->total_items);

  GtkWidget *value_label = create_styled_label(value_str, TRUE, 1.5);
  GtkWidget *items_label = create_styled_label(items_str, FALSE, 1.2);
  GtkWidget *date_label = gtk_label_new(report->generated_at);

  gtk_box_pack_start(GTK_BOX(info_box), value_label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(info_box), items_label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(info_box), date_label, FALSE, FALSE, 0);

  gtk_container_add(GTK_CONTAINER(valuation_view), info_box);
  gtk_widget_show_all(valuation_view);

  report_free_valuation(report);
}

// Wrapper function to match GtkCallback signature
static void destroy_widget(GtkWidget *widget, void *data)
{
  (void)data; // Unused parameter
  gtk_widget_destroy(widget);
}

// Refresh all reports
static void refresh_reports()
{
  // Clear existing content
  gtk_container_foreach(GTK_CONTAINER(out_of_stock_view), destroy_widget, NULL);
  gtk_container_foreach(GTK_CONTAINER(location_view), destroy_widget, NULL);
  gtk_container_foreach(GTK_CONTAINER(recent_products_view), destroy_widget, NULL);
  gtk_container_foreach(GTK_CONTAINER(category_view), destroy_widget, NULL);
  gtk_container_foreach(GTK_CONTAINER(valuation_view), destroy_widget, NULL);

  // Update all views
  update_out_of_stock_view();
  update_location_view();
  update_recent_products_view();
  update_category_view();
  update_valuation_view();
}

// Create the main reports view
GtkWidget *create_reports_view()
{
  content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  // Title
  GtkWidget *title = create_styled_label("Reports Dashboard", TRUE, 2.0);
  gtk_widget_set_margin_top(title, 20);
  gtk_widget_set_margin_bottom(title, 20);
  gtk_box_pack_start(GTK_BOX(content_box), title, FALSE, FALSE, 0);

  // Refresh button
  GtkWidget *refresh_btn = gtk_button_new_with_label("Refresh Reports");
  gtk_widget_set_margin_start(refresh_btn, 10);
  gtk_widget_set_margin_end(refresh_btn, 10);
  gtk_widget_set_margin_bottom(refresh_btn, 10);
  g_signal_connect(refresh_btn, "clicked", G_CALLBACK(refresh_reports), NULL);
  gtk_box_pack_start(GTK_BOX(content_box), refresh_btn, FALSE, FALSE, 0);

  // Create scrolled window
  GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                 GTK_POLICY_NEVER,
                                 GTK_POLICY_AUTOMATIC);
  gtk_widget_set_vexpand(scrolled, TRUE);

  // Create main container for reports
  GtkWidget *reports_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

  // Create sections for each report type
  out_of_stock_view = create_section("Out of Stock Products\nProducts with quantity below minimum threshold (5 units)");
  location_view = create_section("Products by Location\nInventory distribution across storage locations");
  recent_products_view = create_section("Recently Added Products\nLatest products added to the system");
  category_view = create_section("Products by Category\nProduct statistics grouped by category (quantity, value, average)");
  valuation_view = create_section("Stock Valuation\nTotal inventory value and item count summary");

  // Add sections to reports container
  gtk_box_pack_start(GTK_BOX(reports_container), out_of_stock_view, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(reports_container), location_view, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(reports_container), recent_products_view, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(reports_container), category_view, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(reports_container), valuation_view, FALSE, FALSE, 0);

  // Add reports container to scrolled window
  gtk_container_add(GTK_CONTAINER(scrolled), reports_container);
  gtk_box_pack_start(GTK_BOX(content_box), scrolled, TRUE, TRUE, 0);

  // Initial load of reports
  refresh_reports();

  return content_box;
}
