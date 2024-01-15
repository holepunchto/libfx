#include <assert.h>
#include <uv.h>

#include "../include/fx.h"

#include "../fixtures/images/image1.h"

static void
on_launch (fx_t *app) {
  int e;

  fx_view_t *view;
  e = fx_view_init(app, 0.0, 0.0, 256.0, 256.0, &view);
  assert(e == 0);

  fx_image_t *image;
  e = fx_image_init(app, 96.0, 96.0, 64.0, 64.0, &image);
  assert(e == 0);

  e = fx_image_load(image, image1_rgba, 64, 64, -1);
  assert(e == 0);

  e = fx_set_child((fx_node_t *) view, (fx_node_t *) image, 0);
  assert(e == 0);

  fx_window_t *window;
  e = fx_window_init(app, view, 0.0, 0.0, 256.0, 256.0, 0, &window);
  assert(e == 0);

  e = fx_show_window(window);
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
