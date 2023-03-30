#include "../../include/fx.h"
#include "screen.h"

int
fx_screen_destroy (fx_screen_t *screen) {
  delete screen;

  return 0;
}

int
fx_get_main_screen (fx_t *app, fx_screen_t **result) {
  fx_screen_t *screen = new fx_screen_t();

  *result = screen;

  return 0;
}

int
fx_get_screen_bounds (fx_screen_t *screen, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}
