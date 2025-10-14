#include "video.h"

#include "../../include/fx.h"
#include "shared.h"
#include "winui.h"

extern "C" int
fx_video_init(fx_t *app, const char *url, size_t len, float x, float y, float width, float height, int flags, fx_video_t **result) {
  int err;

  hstring hstr;
  err = fx__to_hstring(url, len, hstr);
  if (err < 0) return err;

  auto video = new fx_video_t();

  video->node.type = fx_video_node;

  video->handle.Width(width);
  video->handle.Height(height);

  video->handle.AreTransportControlsEnabled((flags & fx_video_no_controls) == 0);

  video->handle.Source(MediaSource::CreateFromUri(Uri(hstr)));

  video->bounds.x = x;
  video->bounds.y = y;
  video->bounds.width = width;
  video->bounds.height = height;

  *result = video;

  return 0;
}

extern "C" int
fx_video_destroy(fx_video_t *video) {
  delete video;

  return 0;
}

extern "C" int
fx_get_video_data(fx_video_t *video, void **result) {
  *result = video->data;

  return 0;
}

extern "C" int
fx_set_video_data(fx_video_t *video, void *data) {
  video->data = data;

  return 0;
}

extern "C" int
fx_get_video_bounds(fx_video_t *video, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

extern "C" int
fx_set_video_bounds(fx_video_t *video, float x, float y, float width, float height) {
  return 0;
}

bool
fx_is_video_loop(fx_video_t *video) {
  return false;
}

bool
fx_set_video_loop(fx_video_t *video, bool loop) {
  return 0;
}

extern "C" int
fx_play_video(fx_video_t *video) {
  return 0;
}

extern "C" int
fx_pause_video(fx_video_t *video) {
  return 0;
}
