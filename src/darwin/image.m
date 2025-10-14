#import "image.h"

#import "../../include/fx.h"
#import "shared.h"

#import <AppKit/AppKit.h>
#import <CoreGraphics/CoreGraphics.h>

@implementation FXImage

- (BOOL)isFlipped {
  return YES;
}

@end

int
fx_image_init(fx_t *app, float x, float y, float width, float height, fx_image_t **result) {
  FXImage *native_image = [[FXImage alloc] initWithFrame:CGRectMake(x, y, width, height)];

  fx_image_t *image = malloc(sizeof(fx_image_t));

  image->node.type = fx_image_node;

  image->handle = native_image;

  image->size = NSMakeSize(width, height);

  native_image.fxImage = image;

  *result = image;

  return 0;
}

int
fx_image_destroy(fx_image_t *image) {
  if (image->handle.image) [image->handle.image release];

  [image->handle release];

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
  NSRect frame = image->handle.frame;

  if (x) *x = frame.origin.x;
  if (y) *y = frame.origin.y;
  if (width) *width = frame.size.width;
  if (height) *height = frame.size.height;

  return 0;
}

int
fx_set_image_bounds(fx_image_t *image, float x, float y, float width, float height) {
  image->handle.frame = CGRectMake(x, y, width, height);

  return 0;
}

int
fx_image_load_file(fx_image_t *image, const char *path, size_t len) {
  image->handle.image = [[NSImage alloc] initWithContentsOfFile:fx__string(path, len)];

  return 0;
}

int
fx_image_load_pixels(fx_image_t *image, const uint8_t *pixels, int width, int height, int stride) {
  if (stride == -1) stride = width * 4;

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

  image->handle.image = [[NSImage alloc] initWithCGImage:ref size:image->size];

  CGColorSpaceRelease(color_space);

  CGDataProviderRelease(provider);

  CGImageRelease(ref);

  return 0;
}
