#ifndef STOCK_DIALOG_H
#define STOCK_DIALOG_H

#include <gtk/gtk.h>
#include "stock.h"

/**
 * Shows a dialog for creating or editing a stock entry.
 * @param parent The parent window
 * @param stock The stock entry to edit, or NULL for creating a new entry
 */
void show_stock_dialog(GtkWindow *parent, Stock *stock);

#endif // STOCK_DIALOG_H
