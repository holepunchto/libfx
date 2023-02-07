#include "../include/fx.h"

static void
on_launch (fx_t *app) {
  fx_view_t *view;
  fx_view_init(app, 0.0, 0.0, 960.0, 540.0, &view);

  fx_video_t *video;
  fx_video_init(app, "https://interactive-examples.mdn.mozilla.net/media/cc0-videos/flower.mp4", 72, 0.0, 0.0, 960.0, 540.0, &video);

  fx_set_child((fx_node_t *) view, (fx_node_t *) video, 0);

  fx_window_t *window;
  fx_window_init(app, view, 0.0, 0.0, 960.0, 540.0, &window);

  fx_show_window(window);
}

int
main () {
  fx_t *app;
  fx_init(uv_default_loop(), &app);

  fx_on_launch(app, on_launch);

  return fx_run(app);
}
