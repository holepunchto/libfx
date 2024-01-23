#include "../include/fx.h"

#include <assert.h>
#include <uv.h>

static void
on_launch (fx_t *app) {
  int err;

  fx_screen_t *screen;
  err = fx_get_main_screen(app, &screen);
  assert(err == 0);

  float x, y, width, height;
  err = fx_get_screen_bounds(screen, &x, &y, &width, &height);
  assert(err == 0);

  fx_view_t *view;
  err = fx_view_init(app, 0, 0, width, height, &view);
  assert(err == 0);

  fx_text_t *text;
  err = fx_text_init(app, 0.0, 0.0, 100.0, 12.0, &text);
  assert(err == 0);

  fx_text_span_t *span;
  err = fx_append_text_span(text, "Hello world!", -1, &span);
  assert(err == 0);

  err = fx_set_child((fx_node_t *) view, (fx_node_t *) text, 0);
  assert(err == 0);

  fx_window_t *window;
  err = fx_window_init(app, view, x, y, width, height, 0, &window);
  assert(err == 0);
}

static void
on_terminate (fx_t *app) {}

int
main () {
  int err;

  fx_t *app;
  err = fx_init(uv_default_loop(), &app);
  assert(err == 0);

  return fx_run(app, on_launch, on_terminate);
}
