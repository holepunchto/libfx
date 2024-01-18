#include <assert.h>
#include <string.h>
#include <uv.h>

#include "../include/fx.h"

static void
on_launch (fx_t *app) {
  int e;

  fx_view_t *view;
  e = fx_view_init(app, 0.0, 0.0, 100.0, 100.0, &view);

  fx_view_t *content_view;
  e = fx_view_init(app, 0.0, 0.0, 100.0, 500.0, &content_view);

  const char *value = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum varius lacus tincidunt tellus laoreet, ut malesuada orci vulputate. Nunc id lacus sit amet tortor finibus ultricies. Nam pellentesque, nunc efficitur viverra sagittis, sapien dolor sagittis sapien, porttitor hendrerit arcu magna eget risus. Proin maximus lacinia nisl, in imperdiet felis pharetra et. Ut hendrerit gravida dapibus. Nulla sapien urna, mattis sed nibh et, elementum venenatis lacus.";

  fx_text_t *text;
  e = fx_text_init(app, 0.0, 0.0, 100.0, 500.0, &text);
  assert(e == 0);

  fx_text_span_t *span;
  e = fx_append_text_span(text, value, -1, &span);
  assert(e == 0);

  e = fx_set_child((fx_node_t *) content_view, (fx_node_t *) text, 0);
  assert(e == 0);

  fx_scroll_view_t *scroll_view;
  e = fx_scroll_view_init(app, content_view, 0.0, 0.0, 100.0, 100.0, &scroll_view);
  assert(e == 0);

  e = fx_set_child((fx_node_t *) view, (fx_node_t *) scroll_view, 0);
  assert(e == 0);

  fx_window_t *window;
  e = fx_window_init(app, view, 0.0, 0.0, 100.0, 100.0, 0, &window);
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
