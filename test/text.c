#include "../include/fx.h"

int
main () {
  fx_t *app;
  fx_init(uv_default_loop(), &app);

  fx_view_t *view;
  fx_view_init(app, 0.0, 0.0, 200.0, 200.0, &view);

  fx_text_t *text;
  fx_text_init(app, 60.0, 100.0, 80.0, 12.0, &text);

  fx_text_span_t *span;
  fx_append_text_span(text, "Hello world!", 12, &span);

  fx_set_child((fx_node_t *) view, (fx_node_t *) text, 0);

  fx_window_t *window;
  fx_window_init(app, view, 0.0, 0.0, 200.0, 200.0, &window);

  fx_show_window(window);

  return fx_run(app);
}
