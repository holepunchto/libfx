#include <assert.h>

#include "../include/fx.h"

static void
on_launch (fx_t *app) {
  int e;

  fx_view_t *view;
  e = fx_view_init(app, 0.0, 0.0, 200.0, 200.0, &view);
  assert(e == 0);

  fx_text_t *text;
  e = fx_text_init(app, 60.0, 100.0, 80.0, 12.0, &text);
  assert(e == 0);

  fx_text_span_t *span;
  e = fx_append_text_span(text, "Hello world!", 12, &span);
  assert(e == 0);

  e = fx_set_child((fx_node_t *) view, (fx_node_t *) text, 0);
  assert(e == 0);

  fx_window_t *window;
  e = fx_window_init(app, view, 0.0, 0.0, 200.0, 200.0, 0, &window);
  assert(e == 0);
}

int
main () {
  int e;

  fx_t *app;
  e = fx_init(uv_default_loop(), &app);
  assert(e == 0);

  e = fx_on_launch(app, on_launch);
  assert(e == 0);

  return fx_run(app);
}
