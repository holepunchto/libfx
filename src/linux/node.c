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
fx_get_child_widget (fx_node_t *child, float *x, float *y, GtkWidget **result) {
  GtkWidget *child_widget;

  switch (child->type) {
  case fx_view_node: {
    fx_view_t *view = (fx_view_t *) child;

    *x = view->bounds.x;
    *y = view->bounds.y;

    child_widget = GTK_WIDGET(view->handle);
    break;
  }
  case fx_scroll_view_node:
    break;
  case fx_text_node:
    break;
  case fx_text_input_node:
    break;
  case fx_image_node: {
    fx_image_t *image = (fx_image_t *) child;

    *x = image->bounds.x;
    *y = image->bounds.y;

    child_widget = GTK_WIDGET(image->handle);
    break;
  }
  case fx_video_node:
    break;
  case fx_web_view_node:
    break;
  }

  *result = child_widget;

  return 0;
}

int
fx_set_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  int err;

  float x, y;

  GtkWidget *child_widget;
  err = fx_get_child_widget(child, &x, &y, &child_widget);
  if (err < 0) return -1;

  switch (parent->type) {
  case fx_view_node: {
    GtkFixed *handle = ((fx_view_t *) parent)->handle;

    gtk_fixed_put(handle, child_widget, x, y);

    break;
  }
  default:
    return -1;
  }

  return 0;
}

int
fx_unset_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  return 0;
}
