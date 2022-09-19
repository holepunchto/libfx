#import <AVKit/AVKit.h>
#import <AppKit/AppKit.h>

#import "../../../include/fx.h"

@interface FXVideo : AVPlayerView

@property(assign) fx_video_t *fxVideo;

@end

struct fx_video_s {
  fx_node_t node;

  FXVideo *native_video;
};
