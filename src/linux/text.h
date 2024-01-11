#include <gtk/gtk.h>

#include "../../include/fx.h"

struct fx_text_s {
  fx_node_t node;

  GtkLabel* handle;

  GtkWidget *parent;

  struct {
    float x;
    float y;
    float width;
    float height;
  } bounds;

  void *data;
};

struct fx_text_span_s {
  uint32_t start;
  uint32_t end;
};
