#ifndef FX_VIEW_H
#define FX_VIEW_H

#include "../fx.h"

typedef struct fx_view_s fx_view_t;

int
fx_view_init(fx_t *app, float x, float y, float width, float height, fx_view_t **result);

int
fx_view_destroy(fx_view_t *view);

int
fx_get_view_data(fx_view_t *view, void **result);

int
fx_set_view_data(fx_view_t *view, void *data);

int
fx_get_view_bounds(fx_view_t *view, float *x, float *y, float *width, float *height);

int
fx_set_view_bounds(fx_view_t *view, float x, float y, float width, float height);

#endif // FX_VIEW_H
