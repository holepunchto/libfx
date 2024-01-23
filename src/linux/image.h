#ifndef FX_LINUX_IMAGE_H
#define FX_LINUX_IMAGE_H

#include "../../include/fx.h"

#include <gtk/gtk.h>

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

#endif // FX_LINUX_IMAGE_H
