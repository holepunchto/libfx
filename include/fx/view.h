#ifndef FX_VIEW_H
#define FX_VIEW_H

#include "../fx.h"

typedef struct fx_view_s fx_view_t;

int
fx_view_init (fx_t *app, double x, double y, double width, double height, fx_view_t **result);

int
fx_view_destroy (fx_view_t *view);

#endif // FX_VIEW_H
