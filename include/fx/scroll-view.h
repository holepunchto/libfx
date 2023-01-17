#ifndef FX_SCROLL_VIEW_H
#define FX_SCROLL_VIEW_H

#include <stddef.h>

#include "../fx.h"
#include "view.h"

typedef struct fx_scroll_view_s fx_scroll_view_t;

int
fx_scroll_view_init (fx_t *app, fx_view_t *view, double x, double y, double width, double height, fx_scroll_view_t **result);

int
fx_scroll_view_destroy (fx_scroll_view_t *scroll_view);

int
fx_get_scroll_view_data (fx_scroll_view_t *scroll_view, void **result);

int
fx_set_scroll_view_data (fx_scroll_view_t *scroll_view, void *data);

int
fx_get_scroll_view_bounds (fx_scroll_view_t *scroll_view, double *x, double *y, double *width, double *height);

int
fx_set_scroll_view_bounds (fx_scroll_view_t *scroll_view, double x, double y, double width, double height);

#endif // FX_SCROLL_VIEW_H
