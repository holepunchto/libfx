#ifndef FX_TEXT_H
#define FX_TEXT_H

#include <stddef.h>

#include "../fx.h"

typedef struct fx_text_s fx_text_t;
typedef struct fx_text_span_s fx_text_span_t;

int
fx_text_init (fx_t *app, float x, float y, float width, float height, fx_text_t **result);

int
fx_text_destroy (fx_text_t *text);

int
fx_get_text_data (fx_text_t *text, void **result);

int
fx_set_text_data (fx_text_t *text, void *data);

int
fx_get_text_bounds (fx_text_t *text, float *x, float *y, float *width, float *height);

int
fx_get_text_bounds_used (fx_text_t *text, float *x, float *y, float *width, float *height);

int
fx_set_text_bounds (fx_text_t *text, float x, float y, float width, float height);

int
fx_append_text_span (fx_text_t *text, const char *value, size_t len, fx_text_span_t **result);

#endif // FX_TEXT_H
