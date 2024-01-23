#include "video.h"

#include "../../include/fx.h"

#include <stdlib.h>

int
fx_video_init (fx_t *app, const char *url, size_t len, float x, float y, float width, float height, int flags, fx_video_t **result) {
  GtkMediaStream *stream = gtk_media_file_new_for_filename(url);

  if (stream == NULL) return -1;

  GtkWidget *handle;

  if (flags & fx_video_no_controls) {
    handle = gtk_picture_new_for_paintable(GDK_PAINTABLE(stream));
  } else {
    handle = gtk_video_new_for_media_stream(stream);
  }

  if (handle == NULL) return -1;

  fx_video_t *video = malloc(sizeof(fx_video_t));

  video->node.type = fx_video_node;

  video->stream = stream;

  video->handle = handle;

  video->parent = NULL;

  video->bounds.x = x;
  video->bounds.y = y;
  video->bounds.width = width;
  video->bounds.height = height;

  *result = video;

  gtk_widget_set_visible(handle, true);

  gtk_widget_set_size_request(handle, width, height);

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
  if (x) *x = video->bounds.x;
  if (y) *y = video->bounds.y;
  if (width) *width = video->bounds.width;
  if (height) *height = video->bounds.height;

  return 0;
}

int
fx_set_video_bounds (fx_video_t *video, float x, float y, float width, float height) {
  video->bounds.x = x;
  video->bounds.y = y;
  video->bounds.width = width;
  video->bounds.height = height;

  return 0;
}

bool
fx_is_video_loop (fx_video_t *video) {
  return gtk_media_stream_get_loop(video->stream);
}

bool
fx_set_video_loop (fx_video_t *video, bool loop) {
  gtk_media_stream_set_loop(video->stream, loop);

  return 0;
}

int
fx_play_video (fx_video_t *video) {
  gtk_media_stream_play(video->stream);

  return 0;
}

int
fx_pause_video (fx_video_t *video) {
  gtk_media_stream_pause(video->stream);

  return 0;
}
