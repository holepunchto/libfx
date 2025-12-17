#include "screen.h"

#include "../../include/fx.h"

#include <gdk/gdk.h>
#include <stdlib.h>

int
fx_screen_release(fx_screen_t *screen) {
  free(screen);

  return 0;
}

int
fx_get_main_screen(fx_t *app, fx_screen_t **result) {
  GdkDisplay *display = gdk_display_get_default();

  GdkMonitor *monitor = GDK_MONITOR(g_list_model_get_item(gdk_display_get_monitors(display), 0));

  if (monitor == NULL) return -1;

  GdkRectangle rect;

  gdk_monitor_get_geometry(monitor, &rect);

  fx_screen_t *screen = malloc(sizeof(fx_screen_t));

  screen->x = rect.x;
  screen->y = rect.y;
  screen->width = rect.width;
  screen->height = rect.height;

  *result = screen;

  return 0;
}

int
fx_get_screen_bounds(fx_screen_t *screen, float *x, float *y, float *width, float *height) {
  if (x) *x = screen->x;
  if (y) *y = screen->y;
  if (width) *width = screen->width;
  if (height) *height = screen->height;

  return 0;
}
