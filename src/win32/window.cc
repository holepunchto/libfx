#include <assert.h>
#include <uv.h>

#include "../../include/fx.h"
#include "../shared/fx.h"
#include "fx.h"
#include "shared.h"
#include "view.h"
#include "window.h"

static uv_once_t fx_window_class_init = UV_ONCE_INIT;

static ATOM fx_window_class;

static LRESULT CALLBACK
on_window_message (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  auto window = reinterpret_cast<fx_window_t *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

  auto res = DefWindowProc(hwnd, uMsg, wParam, lParam);

  switch (uMsg) {
  case WM_SIZING:
    if (window->on_resize) window->on_resize(window);
    break;

  case WM_MOVING:
    if (window->on_move) window->on_move(window);
    break;

  case WM_CLOSE:
    if (window->on_close) window->on_close(window);
    break;

  case WM_DESTROY:
    if (--fx_main_app->platform->active_windows) return res;

    PostQuitMessage(0);
    break;

  case WM_PAINT:
    if (window->view) {
      RECT rect;

      if (GetClientRect(window->handle, &rect)) {
        SetWindowPos(
          window->view->handle,
          NULL,
          fx__rect_x(rect),
          fx__rect_y(rect),
          fx__rect_width(rect),
          fx__rect_height(rect),
          0
        );
      }
    }
  }

  return res;
}

static void
on_window_class_init () {
  auto instance = GetModuleHandle(NULL);

  WNDCLASSEX window_class;

  ZeroMemory(&window_class, sizeof(WNDCLASSEX));

  window_class.cbSize = sizeof(WNDCLASSEX);
  window_class.lpfnWndProc = on_window_message;
  window_class.hInstance = instance;
  window_class.lpszClassName = "FX Window";

  fx_window_class = RegisterClassEx(&window_class);

  assert(fx_window_class);
}

int
fx_window_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, int flags, fx_window_t **result) {
  uv_once(&fx_window_class_init, on_window_class_init);

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

  DWORD style;

  if (flags & fx_window_no_frame) {
    style = WS_POPUP | WS_BORDER;
  } else {
    style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
  }

  auto rect = fx__rect<float>(0, 0, width, height);

  AdjustWindowRect(&rect, style, FALSE);

  auto instance = GetModuleHandle(NULL);

  auto handle = CreateWindowEx(
    0,
    MAKEINTATOM(fx_window_class),
    NULL,
    style,
    int(x),
    int(y),
    fx__rect_width<int>(rect),
    fx__rect_height<int>(rect),
    NULL,
    NULL,
    instance,
    NULL
  );

  if (handle == NULL) return -1;

  fx_main_app->platform->active_windows++;

  if (view) {
    if (SetParent(view->handle, handle) == NULL) return -1;

    auto success = SetWindowPos(
      view->handle,
      NULL,
      int(x),
      int(y),
      int(width),
      int(height),
      0
    );

    if (!success) return -1;
  }

  auto window = new fx_window_t();

  window->handle = handle;

  window->view = view;

  window->data = NULL;

  window->on_resize = NULL;
  window->on_move = NULL;
  window->on_minimize = NULL;
  window->on_deminimize = NULL;
  window->on_close = NULL;

  *result = window;

  SetWindowLongPtr(handle, GWLP_USERDATA, LONG_PTR(window));

  return 0;
}

int
fx_window_destroy (fx_window_t *window) {
  DestroyWindow(window->handle);

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
  RECT rect;

  auto success = GetWindowRect(window->handle, &rect);

  if (!success) return -1;

  if (x) *x = fx__rect_x<float>(rect);
  if (y) *y = fx__rect_y<float>(rect);
  if (width) *width = fx__rect_width<float>(rect);
  if (height) *height = fx__rect_height<float>(rect);

  return 0;
}

int
fx_set_window_title (fx_window_t *window, const char *title) {
  auto success = SetWindowText(window->handle, title);

  return success ? 0 : -1;
}

int
fx_get_window_title (fx_window_t *window, char *title, size_t len, size_t *result) {
  if (title == NULL) {
    *result = GetWindowTextLength(window->handle);
  } else if (len != 0) {
    int written = GetWindowText(window->handle, title, len);

    if (written < len) title[written] = '\0';

    if (result) *result = written;
  } else if (result) *result = 0;

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

bool
fx_is_window_resizable (fx_window_t *window) {
  return (GetWindowLong(window->handle, GWL_STYLE) & WS_THICKFRAME) != 0;
}

int
fx_set_window_resizable (fx_window_t *window, bool resizable) {
  auto style = GetWindowLong(window->handle, GWL_STYLE);

  if (resizable) {
    style |= WS_THICKFRAME;
  } else {
    style &= ~WS_THICKFRAME;
  }

  SetWindowLong(window->handle, GWL_STYLE, style);

  return 0;
}
