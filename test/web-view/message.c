#include "../include/fx.h"

#include <assert.h>
#include <string.h>

static void
on_message (fx_web_view_t *web_view, const char *message, size_t len) {
  int e;

  printf("%s\n", message);

  e = fx_web_view_post_message(web_view, message, len);
  assert(e == 0);
}

static void
on_launch (fx_t *app) {
  int e;

  fx_view_t *view;
  e = fx_view_init(app, 0.0, 0.0, 1280.0, 720.0, &view);

  fx_web_view_t *web_view;
  e = fx_web_view_init(app, 0.0, 0.0, 1280.0, 720.0, &web_view);
  assert(e == 0);

  e = fx_on_web_view_message(web_view, on_message);
  assert(e == 0);

  char *code =
    "<script>"
    "bridge.addEventListener('message', console.log);"
    "bridge.postMessage('hello world')"
    "</script>";

  e = fx_web_view_load_html(web_view, code, -1);
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

  return fx_run(app, on_launch, NULL);
}
