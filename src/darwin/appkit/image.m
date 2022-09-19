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
