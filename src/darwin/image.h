#import <AppKit/AppKit.h>

#import "../../include/fx.h"

@interface FXImage : NSImageView

@property(assign) fx_image_t *fxImage;

@end

struct fx_image_s {
  fx_node_t node;

  __unsafe_unretained FXImage *handle;

  NSSize size;

  void *data;
};
