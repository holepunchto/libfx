#include "view.h"
#include "../../include/fx.h"

int
fx_view_init (fx_t *app, float x, float y, float width, float height, fx_view_t **result) {
  fx_view_t *view = malloc(sizeof(fx_view_t));

  view->node.type = fx_view_node;

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
