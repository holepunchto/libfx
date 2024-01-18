#include "view.h"
#include "../../include/fx.h"

extern "C" int
fx_view_init (fx_t *app, float x, float y, float width, float height, fx_view_t **result) {
  auto view = new fx_view_t();

  view->node.type = fx_view_node;

  view->handle.Width(width);
  view->handle.Height(height);

  view->handle.HorizontalAlignment(HorizontalAlignment::Left);
  view->handle.VerticalAlignment(VerticalAlignment::Top);

  *result = view;

  return 0;
}

extern "C" int
fx_view_destroy (fx_view_t *view) {
  delete view;

  return 0;
}

extern "C" int
fx_get_view_data (fx_view_t *view, void **result) {
  *result = view->data;

  return 0;
}

extern "C" int
fx_set_view_data (fx_view_t *view, void *data) {
  view->data = data;

  return 0;
}

extern "C" int
fx_get_view_bounds (fx_view_t *view, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

extern "C" int
fx_set_view_bounds (fx_view_t *view, float x, float y, float width, float height) {
  return 0;
}
