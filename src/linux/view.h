#include <gtk/gtk.h>

#include "../../include/fx.h"

struct fx_view_s {
  fx_node_t node;

  GtkFixed *handle;

  void *data;
};
