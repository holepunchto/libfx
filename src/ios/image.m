#import "image.h"

#import "../../include/fx.h"

#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>

@implementation FXImage

@end

int
fx_image_init(fx_t *app, float x, float y, float width, float height, fx_image_t **result) {
  FXImage *native_image = [[FXImage alloc] initWithFrame:CGRectMake(x, y, width, height)];

  fx_image_t *image = malloc(sizeof(fx_image_t));

  image->node.type = fx_image_node;

  image->native_image = native_image;

  image->size = CGSizeMake(width, height);

  native_image.fxImage = image;

  *result = image;

  return 0;
}

int
fx_image_destroy(fx_image_t *image) {
  [image->native_image release];

  free(image);

  return 0;
}

int
fx_get_image_data(fx_image_t *image, void **result) {
  *result = image->data;

  return 0;
}

int
fx_set_image_data(fx_image_t *image, void *data) {
  image->data = data;

  return 0;
}

int
fx_get_image_bounds(fx_image_t *image, float *x, float *y, float *width, float *height) {
  CGRect frame = image->native_image.frame;

  if (x) *x = frame.origin.x;
  if (y) *y = frame.origin.y;
  if (width) *width = frame.size.width;
  if (height) *height = frame.size.height;

  return 0;
}

int
fx_set_image_bounds(fx_image_t *image, float x, float y, float width, float height) {
  image->native_image.frame = CGRectMake(x, y, width, height);

  return 0;
}

int
fx_image_load_file(fx_image_t *image, const char *path, size_t len) {
  image->handle.image = [[UIImage alloc] initWithContentsOfFile:fx__string(path, len)];

  return 0;
}

int
fx_image_load_pixels(fx_image_t *image, const uint8_t *pixels, int width, int height, int stride) {
  CGColorSpaceRef color_space = CGColorSpaceCreateDeviceRGB();

  CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, pixels, stride * height, NULL);

  CGImageRef ref = CGImageCreate(
    width,
    height,
    8,
    32,
    stride,
    color_space,
    (CGBitmapInfo) kCGImageAlphaPremultipliedLast,
    provider,
    NULL,
    YES,
    kCGRenderingIntentDefault
  );

  image->native_image.image = [[UIImage alloc] initWithCGImage:ref];

  CGColorSpaceRelease(color_space);

  CGDataProviderRelease(provider);

  CGImageRelease(ref);

  return 0;
}
