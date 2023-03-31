#include <assert.h>

#include "../include/fx.h"

static void
on_ready (fx_web_view_t *web_view, int status) {
  assert(status == 0);

  fx_web_view_load_url(web_view, "https://example.com", 19);
}

static void
on_launch (fx_t *app) {
  fx_view_t *view;
  fx_view_init(app, 0.0, 0.0, 1280.0, 720.0, &view);

  fx_web_view_t *web_view;
  fx_web_view_init(app, 0.0, 0.0, 1280.0, 720.0, on_ready, &web_view);

  fx_set_child((fx_node_t *) view, (fx_node_t *) web_view, 0);

  fx_window_t *window;
  fx_window_init(app, view, 0.0, 0.0, 1280.0, 720.0, &window);

  fx_show_window(window);
}

int
main () {
  fx_t *app;
  fx_init(uv_default_loop(), &app);

  fx_on_launch(app, on_launch);

  return fx_run(app);
}
