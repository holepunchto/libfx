#include <uv.h>

#include "../include/fx.h"

int
main () {
  fx_t *app;
  fx_init(uv_default_loop(), &app);

  fx_view_t *view;
  fx_view_init(app, 0.0, 0.0, 332.0, 332.0, &view);

  fx_image_t *image;
  fx_image_init(app, "https://interactive-examples.mdn.mozilla.net/media/cc0-images/grapefruit-slice-332-332.jpg", 90, 0.0, 0.0, 332.0, 332.0, &image);

  fx_set_child((fx_node_t *) view, (fx_node_t *) image, 0);

  fx_window_t *window;
  fx_window_init(app, view, 0.0, 0.0, 332.0, 332.0, &window);

  return fx_run(app);
}
