#ifndef PRODUCT_EDIT_VIEW_H
#define PRODUCT_EDIT_VIEW_H

#include <gtk/gtk.h>
#include "services/product/read_product_service.h"

void show_product_edit(GtkWidget *content_area, Product *product);

#endif // PRODUCT_EDIT_VIEW_H
