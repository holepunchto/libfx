#include <stdlib.h>

#include "../../include/fx.h"
#include "scroll-view.h"

int
fx_scroll_view_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, fx_scroll_view_t **result) {
  fx_scroll_view_t *scroll_view = malloc(sizeof(fx_scroll_view_t));

  scroll_view->node.type = fx_scroll_view_node;

  *result = scroll_view;

  return 0;
}

int
fx_scroll_view_destroy (fx_scroll_view_t *scroll_view) {
  free(scroll_view);

  return 0;
}

int
fx_get_scroll_view_data (fx_scroll_view_t *scroll_view, void **result) {
  *result = scroll_view->data;

  return 0;
}

int
fx_set_scroll_view_data (fx_scroll_view_t *scroll_view, void *data) {
  scroll_view->data = data;

  return 0;
}

int
fx_get_scroll_view_bounds (fx_scroll_view_t *scroll_view, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

int
fx_set_scroll_view_bounds (fx_scroll_view_t *scroll_view, float x, float y, float width, float height) {
  return 0;
}
