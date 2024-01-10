#include "../include/fx.h"

static void
on_launch (fx_t *app) {
  fx_window_t *window;
  fx_window_init(app, NULL, 0.0, 0.0, 200.0, 200.0, &window);

  fx_show_window(window);
}

int
main () {
  fx_t *app;
  fx_init(uv_default_loop(), &app);

  fx_on_launch(app, on_launch);

  return fx_run(app);
}
