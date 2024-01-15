#ifndef FX_SCREEN_H
#define FX_SCREEN_H

#include "../fx.h"

typedef struct fx_screen_s fx_screen_t;

/**
 * Symbolic constants for positioning and sizing nodes relative to the screen
 * bounds.
 */
enum {
  // Positions

  /**
   * The midpoint of the screen along the vertical or horizontal axis.
   */
  fx_screen_center = -1,

  // Dimensions

  /**
   * The size of the screen along the vertical or horizontal axis.
   */
  fx_screen_size = -2,
};

int
fx_screen_destroy (fx_screen_t *screen);

int
fx_get_main_screen (fx_t *app, fx_screen_t **result);

int
fx_get_screen_bounds (fx_screen_t *screen, float *x, float *y, float *width, float *height);

#endif // FX_SCREEN_H
