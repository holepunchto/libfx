#include "../../include/fx.h"

#include <gtk/gtk.h>

struct fx_video_s {
  fx_node_t node;

  GtkMediaStream *stream;

  GtkWidget *handle;

  GtkWidget *parent;

  struct {
    float x;
    float y;
    float width;
    float height;
  } bounds;

  void *data;
};
