#include <gtk/gtk.h>
#include <stdlib.h>

#include "../../include/fx.h"
#include "view.h"

int
fx_view_init (fx_t *app, float x, float y, float width, float height, fx_view_t **result) {
  GtkWidget *handle = gtk_fixed_new();

  if (handle == NULL) return -1;

  fx_view_t *view = malloc(sizeof(fx_view_t));

  view->node.type = fx_view_node;

  view->handle = GTK_FIXED(handle);

  *result = view;

  return 0;
}

int
fx_view_destroy (fx_view_t *view) {
  free(view);

  return 0;
}

int
fx_get_view_data (fx_view_t *view, void **result) {
  *result = view->data;

  return 0;
}

int
fx_set_view_data (fx_view_t *view, void *data) {
  view->data = data;

  return 0;
}

int
fx_get_view_bounds (fx_view_t *view, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

int
fx_set_view_bounds (fx_view_t *view, float x, float y, float width, float height) {
  return 0;
}
