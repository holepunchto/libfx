#include "../include/fx.h"

#include <assert.h>

static void
on_close (fx_window_t *window) {
  int e;

  e = fx_window_destroy(window);
  assert(e == 0);
}

static void
on_launch (fx_t *app) {
  int e;

  fx_view_t *view;
  e = fx_view_init(app, 0.0, 0.0, 256.0, 256.0, &view);
  assert(e == 0);

  fx_window_t *window;
  e = fx_window_init(app, view, 0.0, 0.0, 256.0, 256.0, 0, &window);
  assert(e == 0);

  e = fx_on_window_close(window, on_close);
  assert(e == 0);
}

int
main () {
  int e;

  fx_t *app;
  e = fx_init(uv_default_loop(), &app);
  assert(e == 0);

  return fx_run(app, on_launch, NULL);
}
