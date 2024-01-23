#ifndef FX_LINUX_VIEW_H
#define FX_LINUX_VIEW_H

#include "../../include/fx.h"

#include <gtk/gtk.h>

struct fx_view_s {
  fx_node_t node;

  GtkFixed *handle;

  GtkWidget *parent;

  struct {
    float x;
    float y;
    float width;
    float height;
  } bounds;

  void *data;
};

#endif // FX_LINUX_VIEW_H
