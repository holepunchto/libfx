#include <gtk/gtk.h>

#include "../../include/fx.h"
#include "image.h"
#include "scroll-view.h"
#include "text-input.h"
#include "text.h"
#include "video.h"
#include "view.h"
#include "web-view.h"

static inline int
fx_get_parent_view (fx_node_t *parent, GtkWidget **result) {
  *result = NULL;

  return 0;
}

static inline int
fx_get_child_view (fx_node_t *child, GtkWidget **result) {
  *result = NULL;

  return 0;
}

int
fx_set_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  return 0;
}

int
fx_unset_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  return 0;
}
