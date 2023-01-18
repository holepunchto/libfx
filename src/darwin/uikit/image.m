#import <UIKit/UIKit.h>

#import "../../../include/fx.h"
#import "image.h"

@implementation FXImage

@end

int
fx_image_init (fx_t *app, const char *url, size_t len, float x, float y, float width, float height, fx_image_t **result) {
  FXImage *native_image = [[FXImage alloc] initWithFrame:CGRectMake(x, y, width, height)];

  NSData *image_data = [[NSData alloc] initWithContentsOfURL:[[NSURL alloc] initWithString:[[NSString alloc] initWithBytes:url length:len encoding:NSUTF8StringEncoding]]];

  native_image.image = [[UIImage alloc] initWithData:image_data];

  fx_image_t *image = malloc(sizeof(fx_image_t));

  image->node.type = fx_image_node;

  image->native_image = native_image;

  native_image.fxImage = image;

  *result = image;

  return 0;
}
