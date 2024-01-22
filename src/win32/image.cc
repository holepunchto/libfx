#include "image.h"
#include "../../include/fx.h"
#include "winui.h"

extern "C" int
fx_image_init (fx_t *app, float x, float y, float width, float height, fx_image_t **result) {
  auto image = new fx_image_t();

  image->node.type = fx_image_node;

  image->handle.Width(width);
  image->handle.Height(height);

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

int
fx_image_load_data (fx_image_t *image, const uint8_t *pixels, int width, int height, int stride) {
  if (stride == -1) stride = width * 4;

  WriteableBitmap bitmap(width, height);

  auto data = bitmap.PixelBuffer().data();

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width * 4; x += 4) {
      union {
        uint32_t u32;
        uint8_t u8[4];
      } pixel;

      pixel.u32 = (pixels[x + 3] << 24) | (pixels[x] << 16) | (pixels[x + 1] << 8) | pixels[x + 2];

      data[x] = pixel.u8[0];
      data[x + 1] = pixel.u8[1];
      data[x + 2] = pixel.u8[2];
      data[x + 3] = pixel.u8[3];
    }

    pixels += stride;
    data += width * 4;
  }

  image->handle.Source(bitmap);

  return 0;
}
