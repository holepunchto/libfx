#include <assert.h>
#include <uv.h>

#include "../../include/fx.h"
#include "view.h"
#include "window.h"

static uv_once_t fx_window_class_init = UV_ONCE_INIT;

static ATOM fx_window_class;

static LRESULT CALLBACK
on_window_message (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  // TODO: Hook into message and forward to handlers.

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

static void
on_window_class_init () {
  HINSTANCE instance = GetModuleHandle(NULL);

  WNDCLASSEX window_class = {
    .cbSize = sizeof(WNDCLASSEX),
    .lpfnWndProc = on_window_message,
    .hInstance = instance,
    .lpszClassName = "FX Window",
  };

  fx_window_class = RegisterClassEx(&window_class);

  assert(fx_window_class);
}

int
fx_window_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, fx_window_t **result) {
  uv_once(&fx_window_class_init, on_window_class_init);

  HINSTANCE instance = GetModuleHandle(NULL);

  HWND handle = CreateWindowEx(
    0,
    MAKEINTATOM(fx_window_class),
    NULL,
    WS_OVERLAPPEDWINDOW,
    (int) x,
    (int) y,
    (int) width,
    (int) height,
    NULL,
    NULL,
    instance,
    NULL
  );

  if (handle == NULL) return -1;

  if (view) {
    if (SetParent(view->handle, handle) == NULL) return -1;
  }

  fx_window_t *window = malloc(sizeof(fx_window_t));

  window->handle = handle;

  window->data = NULL;

  window->on_resize = NULL;
  window->on_move = NULL;
  window->on_minimize = NULL;
  window->on_deminimize = NULL;

  *result = window;

  return 0;
}

int
fx_window_destroy (fx_window_t *window) {
  free(window);

  return 0;
}

int
fx_on_window_resize (fx_window_t *window, fx_window_resize_cb cb) {
  window->on_resize = cb;

  return 0;
}

int
fx_on_window_move (fx_window_t *window, fx_window_move_cb cb) {
  window->on_move = cb;

  return 0;
}

int
fx_on_window_minimize (fx_window_t *window, fx_window_minimize_cb cb) {
  window->on_minimize = cb;

  return 0;
}

int
fx_on_window_deminimize (fx_window_t *window, fx_window_deminimize_cb cb) {
  window->on_deminimize = cb;

  return 0;
}

int
fx_on_window_close (fx_window_t *window, fx_window_close_cb cb) {
  window->on_close = cb;

  return 0;
}

int
fx_get_window_data (fx_window_t *window, void **result) {
  *result = window->data;

  return 0;
}

int
fx_set_window_data (fx_window_t *window, void *data) {
  window->data = data;

  return 0;
}

int
fx_get_window_bounds (fx_window_t *window, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

bool
fx_is_window_visible (fx_window_t *window) {
  return IsWindowVisible(window->handle);
}

int
fx_set_window_visible (fx_window_t *window, bool visible) {
  ShowWindow(window->handle, visible ? SW_SHOW : SW_HIDE);

  return 0;
}

extern int
fx_show_window (fx_window_t *window);

extern int
fx_hide_window (fx_window_t *window);
