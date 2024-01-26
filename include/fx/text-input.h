#ifndef FX_TEXT_INPUT_H
#define FX_TEXT_INPUT_H

#include "../fx.h"

#include <stdbool.h>

typedef struct fx_text_input_s fx_text_input_t;

typedef void (*fx_text_input_change_cb)(fx_text_input_t *text_input);

int
fx_text_input_init (fx_t *app, float x, float y, float width, float height, fx_text_input_t **result);

int
fx_text_input_destroy (fx_text_input_t *text_input);

int
fx_on_text_input_change (fx_text_input_t *text_input, fx_text_input_change_cb cb);

int
fx_get_text_input_data (fx_text_input_t *text_input, void **result);

int
fx_set_text_input_data (fx_text_input_t *text_input, void *data);

int
fx_get_text_input_bounds (fx_text_input_t *text_input, float *x, float *y, float *width, float *height);

int
fx_set_text_input_bounds (fx_text_input_t *text_input, float x, float y, float width, float height);

int
fx_get_text_input_value (fx_text_input_t *text_input, char *value, size_t len, size_t *result);

int
fx_set_text_input_value (fx_text_input_t *text_input, const char *value, size_t len);

bool
fx_is_text_input_enabled (fx_text_input_t *text_input);

int
fx_set_text_input_enabled (fx_text_input_t *text_input, bool enabled);

bool
fx_is_text_input_selectable (fx_text_input_t *text_input);

int
fx_set_text_input_selectable (fx_text_input_t *text_input, bool selectable);

bool
fx_is_text_input_editable (fx_text_input_t *text_input);

int
fx_set_text_input_editable (fx_text_input_t *text_input, bool editable);

#endif // FX_TEXT_INPUT_H
