#ifndef FX_TEXT_H
#define FX_TEXT_H

#include <stddef.h>

#include "../fx.h"

typedef struct fx_text_s fx_text_t;

int
fx_text_init (fx_t *app, const char *value, size_t len, double x, double y, double width, double height, fx_text_t **result);

int
fx_text_destroy (fx_text_t *text);

int
fx_get_text_data (fx_text_t *text, void **result);

int
fx_set_text_data (fx_text_t *text, void *data);

#endif // FX_TEXT_H
