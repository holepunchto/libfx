#ifndef FX_IMAGE_H
#define FX_IMAGE_H

#include "../fx.h"

#include <stddef.h>
#include <stdint.h>

typedef struct fx_image_s fx_image_t;

int
fx_image_init (fx_t *app, float x, float y, float width, float height, fx_image_t **result);

int
fx_image_destroy (fx_image_t *image);

int
fx_get_image_data (fx_image_t *image, void **result);

int
fx_set_image_data (fx_image_t *image, void *data);

int
fx_get_image_bounds (fx_image_t *image, float *x, float *y, float *width, float *height);

int
fx_set_image_bounds (fx_image_t *image, float x, float y, float width, float height);

int
fx_image_load_file (fx_image_t *image, const char *path, size_t len);

int
fx_image_load_pixels (fx_image_t *image, const uint8_t *pixels, int width, int height, int stride);

#endif // FX_IMAGE_H
