#import "video.h"

#import "../../include/fx.h"

#import <AVKit/AVKit.h>
#import <UIKit/UIKit.h>

@implementation FXVideo

@end

int
fx_video_init(fx_t *app, const char *url, size_t len, float x, float y, float width, float height, fx_video_t **result) {
  FXVideo *native_video = [[FXVideo alloc] init];

  native_video.frame = CGRectMake(x, y, width, height);

  AVPlayerViewController *controller = [[AVPlayerViewController alloc] init];

  controller.view = native_video;

  native_video.controller = controller;

  controller.player = [[AVPlayer alloc] initWithURL:[[NSURL alloc] initWithString:[[NSString alloc] initWithBytes:url length:len encoding:NSUTF8StringEncoding]]];

  fx_video_t *video = malloc(sizeof(fx_video_t));

  video->node.type = fx_video_node;

  video->native_video = native_video;

  native_video.fxVideo = video;

  return 0;
}

int
fx_play_video(fx_video_t *video) {
  [video->native_video.controller.player play];

  return 0;
}

int
fx_pause_video(fx_video_t *video) {
  [video->native_video.controller.player pause];

  return 0;
}
