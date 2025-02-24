#include "utils.h"

gboolean validate_utf8_string(const char *str)
{
  if (!str)
    return FALSE;
  const char *ptr = str;
  while (*ptr)
  {
    gunichar ch = g_utf8_get_char_validated(ptr, -1);
    if (ch == (gunichar)-1 || ch == (gunichar)-2)
      return FALSE;
    ptr = g_utf8_next_char(ptr);
  }
  return TRUE;
}
