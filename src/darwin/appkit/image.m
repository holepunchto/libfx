#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "image.h"

@implementation FXImage

- (BOOL)isFlipped {
  return YES;
}

@end

int
fx_image_init (fx_t *app, const char *url, size_t len, double x, double y, double width, double height, fx_image_t **result) {
  FXImage *native_image = [[FXImage alloc] initWithFrame:CGRectMake(x, y, width, height)];

  native_image.image = [[NSImage alloc] initByReferencingURL:[[NSURL alloc] initWithString:[[NSString alloc] initWithBytes:url length:len encoding:NSUTF8StringEncoding]]];

  fx_image_t *image = malloc(sizeof(fx_image_t));

  image->node.type = fx_image_node;

  image->native_image = native_image;

  native_image.fxImage = image;

  *result = image;

  return 0;
}

int
fx_image_destroy (fx_image_t *image) {
  [image->native_image release];

  free(image);

  return 0;
}

int
fx_get_image_data (fx_image_t *image, void **result) {
  *result = image->data;

  return 0;
}

int
fx_set_image_data (fx_image_t *image, void *data) {
  image->data = data;

  return 0;
}

int
fx_get_image_bounds (fx_image_t *image, double *x, double *y, double *width, double *height) {
  NSRect frame = image->native_image.frame;

  if (x) *x = frame.origin.x;
  if (y) *y = frame.origin.y;
  if (width) *width = frame.size.width;
  if (height) *height = frame.size.height;

  return 0;
}

int
fx_set_image_bounds (fx_image_t *image, double x, double y, double width, double height) {
  image->native_image.frame = CGRectMake(x, y, width, height);

  return 0;
}
