#include "image.h"
#include "../../include/fx.h"

extern "C" int
fx_image_init (fx_t *app, const char *url, size_t len, float x, float y, float width, float height, fx_image_t **result) {
  fx_image_t *image = new fx_image_t();

  image->node.type = fx_image_node;

  *result = image;

  return 0;
}

extern "C" int
fx_image_destroy (fx_image_t *image) {
  delete image;

  return 0;
}

extern "C" int
fx_get_image_data (fx_image_t *image, void **result) {
  *result = image->data;

  return 0;
}

extern "C" int
fx_set_image_data (fx_image_t *image, void *data) {
  image->data = data;

  return 0;
}

extern "C" int
fx_get_image_bounds (fx_image_t *image, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

extern "C" int
fx_set_image_bounds (fx_image_t *image, float x, float y, float width, float height) {
  return 0;
}
