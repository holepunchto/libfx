#import <AVKit/AVKit.h>
#import <AppKit/AppKit.h>

#import "../../include/fx.h"
#import "shared.h"
#import "video.h"

@implementation FXVideo

- (BOOL)isFlipped {
  return YES;
}

@end

int
fx_video_init (fx_t *app, const char *url, size_t len, float x, float y, float width, float height, int flags, fx_video_t **result) {
  FXVideo *handle = [[FXVideo alloc] init];

  handle.frame = CGRectMake(x, y, width, height);

  handle.player = [[AVQueuePlayer alloc] initWithPlayerItem:[[AVPlayerItem alloc] initWithURL:fx__url(url, len)]];

  handle.looper = NULL;

  if (flags & fx_video_no_controls) handle.controlsStyle = AVPlayerViewControlsStyleNone;

  fx_video_t *video = malloc(sizeof(fx_video_t));

  video->node.type = fx_video_node;

  video->handle = handle;

  handle.fxVideo = video;

  *result = video;

  return 0;
}

int
fx_video_destroy (fx_video_t *video) {
  [video->handle.player release];
  [video->handle release];

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
fx_get_video_bounds (fx_video_t *video, float *x, float *y, float *width, float *height) {
  NSRect frame = video->handle.frame;

  if (x) *x = frame.origin.x;
  if (y) *y = frame.origin.y;
  if (width) *width = frame.size.width;
  if (height) *height = frame.size.height;

  return 0;
}

int
fx_set_video_bounds (fx_video_t *video, float x, float y, float width, float height) {
  video->handle.frame = CGRectMake(x, y, width, height);

  return 0;
}

bool
fx_is_video_loop (fx_video_t *video) {
  return video->handle.looper != NULL;
}

bool
fx_set_video_loop (fx_video_t *video, bool loop) {
  AVPlayerLooper *looper = video->handle.looper;

  if (loop) {
    if (looper) return 0;

    video->handle.looper = [[AVPlayerLooper alloc] initWithPlayer:(AVQueuePlayer *) video->handle.player
                                                     templateItem:[video->handle.player currentItem]
                                                        timeRange:kCMTimeRangeInvalid];
  } else {
    if (looper == NULL) return 0;

    video->handle.looper = NULL;

    [looper release];
  }

  return 0;
}

int
fx_play_video (fx_video_t *video) {
  [video->handle.player play];

  return 0;
}

int
fx_pause_video (fx_video_t *video) {
  [video->handle.player pause];

  return 0;
}
