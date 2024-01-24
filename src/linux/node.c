#include "../../include/fx.h"
#include "image.h"
#include "scroll-view.h"
#include "text-input.h"
#include "text.h"
#include "video.h"
#include "view.h"
#include "web-view.h"

#include <gtk/gtk.h>

static inline GtkWidget *
fx_get_child_widget (fx_node_t *child, float *x, float *y) {
  switch (child->type) {
  case fx_view_node: {
    fx_view_t *view = (fx_view_t *) child;

    if (x) *x = view->bounds.x;
    if (y) *y = view->bounds.y;

    return GTK_WIDGET(view->handle);
  }

  case fx_scroll_view_node:
    break;

  case fx_text_node: {
    fx_text_t *text = (fx_text_t *) child;

    if (x) *x = text->bounds.x;
    if (y) *y = text->bounds.y;

    return GTK_WIDGET(text->handle);
  }

  case fx_text_input_node:
    break;

  case fx_image_node: {
    fx_image_t *image = (fx_image_t *) child;

    if (x) *x = image->bounds.x;
    if (y) *y = image->bounds.y;

    return GTK_WIDGET(image->handle);
  }

  case fx_video_node: {
    fx_video_t *video = (fx_video_t *) child;

    if (x) *x = video->bounds.x;
    if (y) *y = video->bounds.y;

    return GTK_WIDGET(video->handle);
  }

  case fx_web_view_node:
    break;
  }

  return NULL;
}

int
fx_set_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  float x, y;

  GtkWidget *child_widget = fx_get_child_widget(child, &x, &y);

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
  GtkWidget *child_widget = fx_get_child_widget(child, NULL, NULL);

  switch (parent->type) {
  case fx_view_node: {
    GtkFixed *handle = ((fx_view_t *) parent)->handle;

    gtk_fixed_remove(handle, child_widget);
    break;
  }

  default:
    return -1;
  }

  return 0;
}
