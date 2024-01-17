#include <assert.h>
#include <uv.h>

#include "../../include/fx.h"
#include "../shared/fx.h"
#include "fx.h"
#include "shared.h"
#include "view.h"
#include "window.h"
#include "winui.h"

struct fx_window : public WindowT<fx_window> {
  fx_window_t *self;

  fx_window(fx_window_t *self) : self(self) {}
};

int
fx_window_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, int flags, fx_window_t **result) {
  int screen_width = GetSystemMetrics(SM_CXSCREEN);
  int screen_height = GetSystemMetrics(SM_CYSCREEN);

  if (x < 0) {
    if (x == fx_screen_center) x = (screen_width - width) / 2;
    else return -1;
  }

  if (y < 0) {
    if (y == fx_screen_center) y = (screen_height - height) / 2;
    else return -1;
  }

  if (width < 0) {
    if (width == fx_screen_size) width = screen_width;
    else return -1;
  }

  if (height < 0) {
    if (height == fx_screen_size) height = screen_height;
    else return -1;
  }

  auto window = new fx_window_t();

  window->handle = make<fx_window>(window);

  window->handle.Activate();

  window->view = view;

  window->data = NULL;

  window->on_resize = NULL;
  window->on_move = NULL;
  window->on_minimize = NULL;
  window->on_deminimize = NULL;
  window->on_close = NULL;

  *result = window;

  return 0;
}

int
fx_window_destroy (fx_window_t *window) {
  delete window;

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

int
fx_set_window_title (fx_window_t *window, const char *title) {
  return 0;
}

int
fx_get_window_title (fx_window_t *window, char *title, size_t len, size_t *result) {
  if (result) *result = 0;

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

bool
fx_is_window_resizable (fx_window_t *window) {
  return false;
}

int
fx_set_window_resizable (fx_window_t *window, bool resizable) {
  return 0;
}
