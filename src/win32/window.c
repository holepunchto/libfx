#include "window.h"
#include "../../include/fx.h"

int
fx_window_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, fx_window_t **result) {
  fx_window_t *window = malloc(sizeof(fx_window_t));

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
  return false;
}

int
fx_set_window_visible (fx_window_t *window, bool visible) {
  return 0;
}

extern int
fx_show_window (fx_window_t *window);

extern int
fx_hide_window (fx_window_t *window);
