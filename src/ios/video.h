#import <AVKit/AVKit.h>
#import <UIKit/UIKit.h>

#import "../../include/fx.h"

@interface FXVideo : UIView

@property(assign) AVPlayerViewController *controller;

@property(assign) fx_video_t *fxVideo;

@end

struct fx_video_s {
  fx_node_t node;

  FXVideo *native_video;
};
