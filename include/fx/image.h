#ifndef FX_IMAGE_H
#define FX_IMAGE_H

#include <stddef.h>

#include "../fx.h"

typedef struct fx_image_s fx_image_t;

int
fx_image_init (fx_t *app, const char *url, size_t len, double x, double y, double width, double height, fx_image_t **result);

int
fx_image_destroy (fx_image_t *image);

int
fx_get_image_data (fx_image_t *image, void **result);

int
fx_set_image_data (fx_image_t *image, void *data);

int
fx_get_image_bounds (fx_image_t *image, double *x, double *y, double *width, double *height);

int
fx_set_image_bounds (fx_image_t *image, double x, double y, double width, double height);

#endif // FX_IMAGE_H
