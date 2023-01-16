#ifndef FX_SCREEN_H
#define FX_SCREEN_H

#include "../fx.h"

typedef struct fx_screen_s fx_screen_t;

int
fx_screen_destroy (fx_screen_t *screen);

int
fx_get_main_screen (fx_t *app, fx_screen_t **result);

int
fx_get_screen_bounds (fx_screen_t *screen, double *x, double *y, double *width, double *height);

#endif // FX_SCREEN_H
