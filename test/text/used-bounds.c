#include "../include/fx.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

static void
on_launch(fx_t *app) {
  int e;

  fx_view_t *view;
  e = fx_view_init(app, 0.0, 0.0, 200.0, 200.0, &view);
  assert(e == 0);

  fx_text_t *text;
  e = fx_text_init(app, 0.0, 0.0, 200.0, NAN, &text);
  assert(e == 0);

  fx_text_span_t *span;
  e = fx_append_text_span(text, "Hello world!", -1, &span);
  assert(e == 0);

  float height;
  e = fx_get_text_bounds_used(text, NULL, NULL, NULL, &height);
  assert(e == 0);

  printf("height=%f\n", height);

  e = fx_set_text_bounds(text, 0.0, 0.0, 200.0, height);
  assert(e == 0);

  e = fx_set_child((fx_node_t *) view, (fx_node_t *) text, 0);
  assert(e == 0);

  fx_window_t *window;
  e = fx_window_init(app, view, 0.0, 0.0, 200.0, 200.0, 0, &window);
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
