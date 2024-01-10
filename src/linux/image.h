#include <gtk/gtk.h>

#include "../../include/fx.h"

struct fx_image_s {
  fx_node_t node;

  GtkPicture *handle;

  GtkWidget *parent;

  struct {
    float x;
    float y;
    float width;
    float height;
  } bounds;

  void *data;
};
