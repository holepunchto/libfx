#include <uv.h>

#include "../include/fx.h"

int
main () {
  fx_t *app;
  fx_init(uv_default_loop(), &app);

  fx_view_t *view;
  fx_view_init(app, 0.0, 0.0, 100.0, 100.0, &view);

  fx_view_t *content_view;
  fx_view_init(app, 0.0, 0.0, 100.0, 500.0, &content_view);

  const char *value = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum varius lacus tincidunt tellus laoreet, ut malesuada orci vulputate. Nunc id lacus sit amet tortor finibus ultricies. Nam pellentesque, nunc efficitur viverra sagittis, sapien dolor sagittis sapien, porttitor hendrerit arcu magna eget risus. Proin maximus lacinia nisl, in imperdiet felis pharetra et. Ut hendrerit gravida dapibus. Nulla sapien urna, mattis sed nibh et, elementum venenatis lacus.";

  fx_text_t *text;
  fx_text_init(app, 0.0, 0.0, 100.0, 500.0, &text);

  fx_text_span_t *span;
  fx_append_text_span(text, value, strlen(value), &span);

  fx_set_child((fx_node_t *) content_view, (fx_node_t *) text, 0);

  fx_scroll_view_t *scroll_view;
  fx_scroll_view_init(app, content_view, 0.0, 0.0, 100.0, 100.0, &scroll_view);

  fx_set_child((fx_node_t *) view, (fx_node_t *) scroll_view, 0);

  fx_window_t *window;
  fx_window_init(app, view, 0.0, 0.0, 100.0, 100.0, &window);

  fx_show_window(window);

  return fx_run(app);
}
