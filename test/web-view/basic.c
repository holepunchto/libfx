#include <assert.h>

#include "../include/fx.h"

static void
on_ready (fx_web_view_t *web_view, int status) {
  int e;

  assert(status == 0);

  e = fx_web_view_load_url(web_view, "https://example.com", 19);
  assert(e == 0);
}

static void
on_launch (fx_t *app) {
  int e;

  fx_view_t *view;
  e = fx_view_init(app, 0.0, 0.0, 1280.0, 720.0, &view);
  assert(e == 0);

  fx_web_view_t *web_view;
  e = fx_web_view_init(app, "web-view", 0.0, 0.0, 1280.0, 720.0, on_ready, &web_view);
  assert(e == 0);

  e = fx_set_child((fx_node_t *) view, (fx_node_t *) web_view, 0);
  assert(e == 0);

  fx_window_t *window;
  e = fx_window_init(app, view, 0.0, 0.0, 1280.0, 720.0, 0, &window);
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
