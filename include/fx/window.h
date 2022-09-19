#ifndef FX_WINDOW_H
#define FX_WINDOW_H

#include "../fx.h"
#include "view.h"

typedef struct fx_window_s fx_window_t;

typedef void (*fx_window_resize_cb)(fx_window_t *window);
typedef void (*fx_window_move_cb)(fx_window_t *window);
typedef void (*fx_window_minimize_cb)(fx_window_t *window);
typedef void (*fx_window_deminimize_cb)(fx_window_t *window);
typedef void (*fx_window_close_cb)(fx_window_t *window);

int
fx_window_init (fx_t *app, fx_view_t *view, double x, double y, double width, double height, fx_window_t **result);

int
fx_window_destroy (fx_window_t *window);

int
fx_on_window_resize (fx_window_t *window, fx_window_resize_cb cb);

int
fx_on_window_move (fx_window_t *window, fx_window_move_cb cb);

int
fx_on_window_minimize (fx_window_t *window, fx_window_minimize_cb cb);

int
fx_on_window_deminimize (fx_window_t *window, fx_window_deminimize_cb cb);

int
fx_on_window_close (fx_window_t *window, fx_window_close_cb cb);

int
fx_get_window_data (fx_window_t *window, void **result);

int
fx_set_window_data (fx_window_t *window, void *data);

int
fx_get_window_bounds (fx_window_t *window, double *x, double *y, double *width, double *height);

int
fx_set_window_bounds (fx_window_t *window, double x, double y, double width, double height);

#endif // FX_WINDOW_H
