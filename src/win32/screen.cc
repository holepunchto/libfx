// Get access to APIs available as of Windows 10 "Redstone 5", which is the
// earliest version that supports WinUI 3.
#define NTDDI_VERSION NTDDI_WIN10_RS5

#include "screen.h"

#include "../../include/fx.h"
#include "window.h"
#include "winui.h"

#include <shellscalingapi.h> // Must be included after uv.h
#include <uv.h>

extern "C" int
fx_screen_release (fx_screen_t *screen) {
  delete screen;

  return 0;
}

static inline int
fx_get_screen (HMONITOR monitor, fx_screen_t **result) {
  if (monitor == NULL) return -1;

  MONITORINFO info;

  info.cbSize = sizeof(MONITORINFO);

  auto success = GetMonitorInfo(monitor, &info);

  if (!success) return -1;

  UINT dpi;

  auto res = GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpi, &dpi);

  if (FAILED(res)) return -1;

  auto rect = info.rcMonitor;

  auto scale = float(dpi) / 96;

  fx_screen_t *screen = new fx_screen_t();

  screen->handle = monitor;

  screen->x = rect.left / scale;
  screen->y = rect.top / scale;
  screen->width = (rect.right - rect.left) / scale;
  screen->height = (rect.bottom - rect.top) / scale;

  screen->scale = scale;

  *result = screen;

  return 0;
}

extern "C" int
fx_get_screen_at (fx_t *app, float x, float y, fx_screen_t **result) {
  return fx_get_screen(MonitorFromPoint({LONG(x), LONG(y)}, MONITOR_DEFAULTTONEAREST), result);
}

extern "C" int
fx_get_main_screen (fx_t *app, fx_screen_t **result) {
  return fx_get_screen(MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY), result);
}

extern "C" int
fx_get_current_screen (fx_window_t *window, fx_screen_t **result) {
  return fx_get_screen(MonitorFromWindow(GetWindowFromWindowId(window->handle.AppWindow().Id()), MONITOR_DEFAULTTONEAREST), result);
}

extern "C" int
fx_get_screen_bounds (fx_screen_t *screen, float *x, float *y, float *width, float *height) {
  if (x) *x = screen->x;
  if (y) *y = screen->y;
  if (width) *width = screen->width;
  if (height) *height = screen->height;

  return 0;
}

extern "C" int
fx_get_screen_scale (fx_screen_t *screen, float *result) {
  *result = screen->scale;

  return 0;
}
