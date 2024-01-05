#include <uv.h>

#include "../include/fx.h"
#include "fixtures/images/image1.h"

static void
on_launch (fx_t *app) {
  fx_view_t *view;
  fx_view_init(app, 0.0, 0.0, 256.0, 256.0, &view);

  fx_image_t *image;
  fx_image_init(app, 96.0, 96.0, 64.0, 64.0, &image);

  fx_image_load(image, image1_rgba, 64, 64, -1);

  fx_set_child((fx_node_t *) view, (fx_node_t *) image, 0);

  fx_window_t *window;
  fx_window_init(app, view, 0.0, 0.0, 256.0, 256.0, &window);

  fx_show_window(window);
}

int
main () {
  fx_t *app;
  fx_init(uv_default_loop(), &app);

  fx_on_launch(app, on_launch);

  return fx_run(app);
}
