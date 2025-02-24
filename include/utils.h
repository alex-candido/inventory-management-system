#ifndef UTILS_H
#define UTILS_H

#include <glib.h>

// Function to validate UTF-8 strings
gboolean validate_utf8_string(const char *str);

// Seed functions for database initialization
void seed_products(void);
void seed_stocks(void);

#endif // UTILS_H
