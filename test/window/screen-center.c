#include "../include/fx.h"

#include <assert.h>

static void
on_launch(fx_t *app) {
  int e;

  fx_screen_t *screen;
  e = fx_get_main_screen(app, &screen);
  assert(e == 0);

  float width, height;
  e = fx_get_screen_bounds(screen, NULL, NULL, &width, &height);
  assert(e == 0);

  fx_view_t *view;
  e = fx_view_init(app, 0.0, 0.0, 256.0, 256.0, &view);
  assert(e == 0);

  fx_window_t *window;
  e = fx_window_init(app, view, (width - 256) / 2, (height - 256) / 2, 256.0, 256.0, 0, &window);
  assert(e == 0);

  e = fx_screen_release(screen);
  assert(e == 0);

  e = fx_activate_window(window);
  assert(e == 0);
}

int
main() {
  int e;

  fx_t *app;
  e = fx_init(uv_default_loop(), &app);
  assert(e == 0);

  return fx_run(app, on_launch, NULL);
}
