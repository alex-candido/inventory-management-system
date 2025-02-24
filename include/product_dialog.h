#ifndef PRODUCT_DIALOG_H
#define PRODUCT_DIALOG_H

#include <gtk/gtk.h>
#include "product.h"

/**
 * Function to show the product dialog.
 * @param parent The parent window
 * @param product The product entry to edit, or NULL for creating a new entry
 */
void show_product_dialog(GtkWindow *parent, Product *product);

#endif /* PRODUCT_DIALOG_H */
