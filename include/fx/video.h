#ifndef FX_VIDEO_H
#define FX_VIDEO_H

#include <stddef.h>

#include "../fx.h"

typedef struct fx_video_s fx_video_t;

enum {
  fx_video_no_controls = 0x1,
};

int
fx_video_init (fx_t *app, const char *url, size_t len, float x, float y, float width, float height, int flags, fx_video_t **result);

int
fx_video_destroy (fx_video_t *video);

int
fx_get_video_data (fx_video_t *video, void **result);

int
fx_set_video_data (fx_video_t *video, void *data);

int
fx_get_video_bounds (fx_video_t *video, float *x, float *y, float *width, float *height);

int
fx_set_video_bounds (fx_video_t *video, float x, float y, float width, float height);

bool
fx_is_video_loop (fx_video_t *video);

bool
fx_set_video_loop (fx_video_t *video, bool loop);

int
fx_play_video (fx_video_t *video);

int
fx_pause_video (fx_video_t *video);

#endif // FX_VIDEO_H
