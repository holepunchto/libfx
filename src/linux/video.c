#include <stdlib.h>

#include "../../include/fx.h"
#include "video.h"

int
fx_video_init (fx_t *app, const char *url, size_t len, float x, float y, float width, float height, fx_video_t **result) {
  fx_video_t *video = malloc(sizeof(fx_video_t));

  video->node.type = fx_video_node;

  return 0;
}

int
fx_video_destroy (fx_video_t *video) {
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
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

int
fx_set_video_bounds (fx_video_t *video, float x, float y, float width, float height) {
  return 0;
}

int
fx_play_video (fx_video_t *video) {
  return 0;
}

int
fx_pause_video (fx_video_t *video) {
  return 0;
}
