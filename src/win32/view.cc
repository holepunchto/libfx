#include "view.h"
#include "../../include/fx.h"

static const char *fx_view_class = "STATIC";

extern "C" int
fx_view_init (fx_t *app, float x, float y, float width, float height, fx_view_t **result) {
  HINSTANCE instance = GetModuleHandle(NULL);

  HWND handle = CreateWindowEx(
    0,
    fx_view_class,
    NULL,
    WS_VISIBLE | WS_CHILD,
    (int) x,
    (int) y,
    (int) width,
    (int) height,
    HWND_MESSAGE,
    NULL,
    instance,
    NULL
  );

  if (handle == NULL) return -1;

  fx_view_t *view = new fx_view_t();

  view->node.type = fx_view_node;

  view->handle = handle;

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
