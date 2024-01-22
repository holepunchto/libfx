#include "window.h"
#include "../../include/fx.h"
#include "../shared/fx.h"
#include "fx.h"
#include "screen.h"
#include "shared.h"
#include "view.h"
#include "winui.h"

extern "C" int
fx_window_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, int flags, fx_window_t **result) {
  int err;

  fx_screen_t *screen;
  err = fx_get_screen_at(app, x, y, &screen);
  if (err < 0) return -1;

  x *= screen->scale;
  y *= screen->scale;
  width *= screen->scale;
  height *= screen->scale;

  err = fx_screen_release(screen);
  assert(err == 0);

  auto window = new fx_window_t();

  window->handle.Title(L"");

  if (flags & fx_window_no_frame) {
    auto presenter = OverlappedPresenter::CreateForDialog();

    presenter.SetBorderAndTitleBar(false, false);

    window->handle.AppWindow().SetPresenter(presenter);
  }

  window->handle.AppWindow().Move({int(x), int(y)});
  window->handle.AppWindow().ResizeClient({int(width), int(height)});

  window->view = view;

  if (view) window->handle.Content(view->handle);

  window->handle.Activate();

  window->data = NULL;

  window->on_resize = NULL;
  window->on_move = NULL;
  window->on_minimize = NULL;
  window->on_deminimize = NULL;
  window->on_close = NULL;

  *result = window;

  return 0;
}

extern "C" int
fx_window_destroy (fx_window_t *window) {
  delete window;

  return 0;
}

extern "C" int
fx_on_window_resize (fx_window_t *window, fx_window_resize_cb cb) {
  window->on_resize = cb;

  return 0;
}

extern "C" int
fx_on_window_move (fx_window_t *window, fx_window_move_cb cb) {
  window->on_move = cb;

  return 0;
}

extern "C" int
fx_on_window_minimize (fx_window_t *window, fx_window_minimize_cb cb) {
  window->on_minimize = cb;

  return 0;
}

extern "C" int
fx_on_window_deminimize (fx_window_t *window, fx_window_deminimize_cb cb) {
  window->on_deminimize = cb;

  return 0;
}

extern "C" int
fx_on_window_close (fx_window_t *window, fx_window_close_cb cb) {
  window->on_close = cb;

  return 0;
}

extern "C" int
fx_get_window_data (fx_window_t *window, void **result) {
  *result = window->data;

  return 0;
}

extern "C" int
fx_set_window_data (fx_window_t *window, void *data) {
  window->data = data;

  return 0;
}

extern "C" int
fx_get_window_bounds (fx_window_t *window, float *x, float *y, float *width, float *height) {
  auto bounds = window->handle.Bounds();

  if (x) *x = bounds.X;
  if (y) *y = bounds.Y;
  if (width) *width = bounds.Width;
  if (height) *height = bounds.Height;

  return 0;
}

extern "C" int
fx_set_window_title (fx_window_t *window, const char *title) {
  return 0;
}

extern "C" int
fx_get_window_title (fx_window_t *window, char *title, size_t len, size_t *result) {
  if (result) *result = 0;

  return 0;
}

extern "C" bool
fx_is_window_resizable (fx_window_t *window) {
  return false;
}

extern "C" int
fx_set_window_resizable (fx_window_t *window, bool resizable) {
  return 0;
}

extern "C" int
fx_close_window (fx_window_t *window) {
  window->handle.Close();

  return 0;
}
