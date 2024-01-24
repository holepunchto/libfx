#ifndef FX_WINDOW_H
#define FX_WINDOW_H

#include <stdbool.h>

#include "../fx.h"
#include "view.h"

typedef struct fx_window_s fx_window_t;

typedef void (*fx_window_resize_cb)(fx_window_t *window);
typedef void (*fx_window_move_cb)(fx_window_t *window);
typedef void (*fx_window_minimize_cb)(fx_window_t *window);
typedef void (*fx_window_deminimize_cb)(fx_window_t *window);
typedef void (*fx_window_close_cb)(fx_window_t *window);

enum {
  fx_window_no_frame = 0x1
};

int
fx_window_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, int flags, fx_window_t **result);

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
fx_get_window_bounds (fx_window_t *window, float *x, float *y, float *width, float *height);

int
fx_get_window_title (fx_window_t *window, char *title, size_t len, size_t *result);

int
fx_set_window_title (fx_window_t *window, const char *title, size_t len);

bool
fx_is_window_resizable (fx_window_t *window);

int
fx_set_window_resizable (fx_window_t *window, bool resizable);

int
fx_close_window (fx_window_t *window);

#endif // FX_WINDOW_H
