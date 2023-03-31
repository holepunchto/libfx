#include "../include/fx.h"

static void
on_message (fx_web_view_t *web_view, const char *message) {
  printf("%s\n", message);

  fx_web_view_post_message(web_view, message);
}

static void
on_ready (fx_web_view_t *web_view, int status) {
  fx_on_web_view_message(web_view, on_message);

  char *code =
    "<script>"
    "bridge.addEventListener('message', console.log);"
    "bridge.postMessage('hello world')"
    "</script>";

  fx_web_view_load_html(
    web_view,
    code,
    strlen(code)
  );
}

static void
on_launch (fx_t *app) {
  fx_view_t *view;
  fx_view_init(app, 0.0, 0.0, 1280.0, 720.0, &view);

  fx_web_view_t *web_view;
  fx_web_view_init(app, "web-view-message", 0.0, 0.0, 1280.0, 720.0, on_ready, &web_view);

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
