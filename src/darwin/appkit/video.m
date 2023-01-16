#import <AVKit/AVKit.h>
#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "video.h"

@implementation FXVideo

- (BOOL)isFlipped {
  return YES;
}

@end

int
fx_video_init (fx_t *app, const char *url, size_t len, double x, double y, double width, double height, fx_video_t **result) {
  FXVideo *native_video = [[FXVideo alloc] init];

  native_video.frame = CGRectMake(x, y, width, height);

  native_video.player = [[AVPlayer alloc] initWithURL:[[NSURL alloc] initWithString:[[NSString alloc] initWithBytes:url length:len encoding:NSUTF8StringEncoding]]];

  fx_video_t *video = malloc(sizeof(fx_video_t));

  video->node.type = fx_video_node;

  video->native_video = native_video;

  native_video.fxVideo = video;

  return 0;
}

int
fx_video_destroy (fx_video_t *video) {
  [video->native_video release];

  free(video);

  return 0;
}

int
fx_get_video_data (fx_video_t *video, void **result) {
  *result = video->data;

  return 0;
}

int
fx_set_video_data (fx_video_t *video, void *data) {
  video->data = data;

  return 0;
}

int
fx_get_video_bounds (fx_video_t *video, double *x, double *y, double *width, double *height) {
  NSRect frame = video->native_video.frame;

  if (x) *x = frame.origin.x;
  if (y) *y = frame.origin.y;
  if (width) *width = frame.size.width;
  if (height) *height = frame.size.height;

  return 0;
}

int
fx_set_video_bounds (fx_video_t *video, double x, double y, double width, double height) {
  video->native_video.frame = CGRectMake(x, y, width, height);

  return 0;
}

int
fx_play_video (fx_video_t *video) {
  [video->native_video.player play];

  return 0;
}

int
fx_pause_video (fx_video_t *video) {
  [video->native_video.player pause];

  return 0;
}
