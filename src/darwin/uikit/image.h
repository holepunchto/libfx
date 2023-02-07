#import <UIKit/UIKit.h>

#import "../../../include/fx.h"

@interface FXImage : UIImageView

@property(assign) fx_image_t *fxImage;

@end

struct fx_image_s {
  fx_node_t node;

  FXImage *native_image;

  void *data;
};
