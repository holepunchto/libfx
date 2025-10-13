#include "../include/fx.h"

#include <assert.h>

static void
on_launch(fx_t *app) {
  int e;

  fx_view_t *view;
  e = fx_view_init(app, 0.0, 0.0, 100.0, 100.0, &view);
  assert(e == 0);

  fx_text_input_t *text_input;
  e = fx_text_input_init(app, 0.0, 0.0, 100.0, 100.0, &text_input);
  assert(e == 0);

  e = fx_set_child((fx_node_t *) view, (fx_node_t *) text_input, 0);
  assert(e == 0);

  fx_window_t *window;
  e = fx_window_init(app, view, 0.0, 0.0, 100.0, 100.0, 0, &window);
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
