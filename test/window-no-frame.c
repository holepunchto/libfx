#include "../include/fx.h"

static void
on_launch (fx_t *app) {
  fx_view_t *view;
  fx_view_init(app, 0.0, 0.0, 256.0, 256.0, &view);

  fx_window_t *window;
  fx_window_init(app, view, 0.0, 0.0, 256.0, 256.0, fx_window_no_frame, &window);

  fx_show_window(window);
}

int
main () {
  fx_t *app;
  fx_init(uv_default_loop(), &app);

  fx_on_launch(app, on_launch);

  return fx_run(app);
}
