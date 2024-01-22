#include <gdk/gdk.h>
#include <stdlib.h>

#include "../../include/fx.h"
#include "screen.h"

int
fx_screen_release (fx_screen_t *screen) {
  g_object_unref(screen->monitor);

  free(screen);

  return 0;
}

int
fx_get_main_screen (fx_t *app, fx_screen_t **result) {
  GdkDisplay *display = gdk_display_get_default();

  GdkMonitor *monitor = GDK_MONITOR(g_list_model_get_item(gdk_display_get_monitors(display), 0));

  if (monitor == NULL) return -1;

  g_object_ref(monitor);

  fx_screen_t *screen = malloc(sizeof(fx_screen_t));

  screen->monitor = monitor;

  *result = screen;

  return 0;
}

int
fx_get_screen_bounds (fx_screen_t *screen, float *x, float *y, float *width, float *height) {
  GdkRectangle rect;

  gdk_monitor_get_geometry(screen->monitor, &rect);

  if (x) *x = rect.x;
  if (y) *y = rect.y;
  if (width) *width = rect.width;
  if (height) *height = rect.height;

  return 0;
}
