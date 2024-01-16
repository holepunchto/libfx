#import <AVKit/AVKit.h>
#import <AppKit/AppKit.h>

#import "../../include/fx.h"

@interface FXVideo : AVPlayerView

@property(assign) fx_video_t *fxVideo;

@property(assign) AVPlayerLooper *looper;

@end

struct fx_video_s {
  fx_node_t node;

  __unsafe_unretained FXVideo *handle;

  void *data;
};
