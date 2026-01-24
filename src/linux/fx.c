#include "../../include/fx.h"

#include "../shared/fx.h"
#include "platform.h"

#include <gtk/gtk.h>
#include <stdlib.h>

typedef struct fx_dispatch_s fx_dispatch_t;

struct fx_dispatch_s {
  fx_dispatch_cb cb;
  void *data;
};

static int
fx__on_dispatch(void *data) {
  fx_dispatch_t *dispatch = (fx_dispatch_t *) data;

  dispatch->cb(fx_main_app, dispatch->data);

  free(dispatch);

  return 0;
}

int
fx_run(fx_t *app, fx_launch_cb on_launch, fx_terminate_cb on_terminate) {
  app->platform->on_launch = on_launch;
  app->platform->on_terminate = on_terminate;

  g_application_run(G_APPLICATION(app->platform->app), 0, NULL);

  exit(0);

  return 0;
}

int
fx_dispatch(fx_dispatch_cb cb, void *data) {
  fx_dispatch_t *dispatch = malloc(sizeof(fx_dispatch_t));

  dispatch->cb = cb;
  dispatch->data = data;

  g_idle_add(fx__on_dispatch, dispatch);

  return 0;
}
