#ifndef FX_VIDEO_H
#define FX_VIDEO_H

#include <stddef.h>

#include "../fx.h"

typedef struct fx_video_s fx_video_t;

int
fx_video_init (fx_t *app, const char *url, size_t len, double x, double y, double width, double height, fx_video_t **result);

int
fx_video_destroy (fx_video_t *video);

int
fx_play_video (fx_video_t *text);

int
fx_pause_video (fx_video_t *text);

#endif // FX_VIDEO_H
