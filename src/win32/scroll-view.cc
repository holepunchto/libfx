#include "scroll-view.h"
#include "../../include/fx.h"

extern "C" int
fx_scroll_view_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, fx_scroll_view_t **result) {
  auto scroll_view = new fx_scroll_view_t();

  scroll_view->node.type = fx_scroll_view_node;

  *result = scroll_view;

  return 0;
}

extern "C" int
fx_scroll_view_destroy (fx_scroll_view_t *scroll_view) {
  delete scroll_view;

  return 0;
}

extern "C" int
fx_get_scroll_view_data (fx_scroll_view_t *scroll_view, void **result) {
  *result = scroll_view->data;

  return 0;
}

extern "C" int
fx_set_scroll_view_data (fx_scroll_view_t *scroll_view, void *data) {
  scroll_view->data = data;

  return 0;
}

extern "C" int
fx_get_scroll_view_bounds (fx_scroll_view_t *scroll_view, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

extern "C" int
fx_set_scroll_view_bounds (fx_scroll_view_t *scroll_view, float x, float y, float width, float height) {
  return 0;
}
