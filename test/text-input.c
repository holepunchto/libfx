#include "../include/fx.h"

static void
on_launch (fx_t *app) {
  fx_view_t *view;
  fx_view_init(app, 0.0, 0.0, 100.0, 100.0, &view);

  fx_text_input_t *text_input;
  fx_text_input_init(app, 0.0, 0.0, 100.0, 100.0, &text_input);

  fx_set_child((fx_node_t *) view, (fx_node_t *) text_input, 0);

  fx_window_t *window;
  fx_window_init(app, view, 0.0, 0.0, 100.0, 100.0, &window);

  fx_show_window(window);
}

int
main () {
  fx_t *app;
  fx_init(uv_default_loop(), &app);

  fx_on_launch(app, on_launch);

  return fx_run(app);
}
