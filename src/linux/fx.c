#include <gtk/gtk.h>
#include <stdlib.h>

#include "../../include/fx.h"
#include "../shared/fx.h"
#include "fx.h"

typedef struct fx_dispatch_s fx_dispatch_t;

struct fx_dispatch_s {
  fx_dispatch_cb cb;
  void *data;
};

static void
on_activate (GtkApplication *gtk, gpointer data) {
  fx_t *app = fx_main_app;

  if (app->platform->on_launch) app->platform->on_launch(app);
}

int
fx_platform_init (fx_t *app, fx_platform_t **result) {
  fx_platform_t *platform = malloc(sizeof(fx_platform_t));

  if (fx_is_main(app)) {
    platform->app = gtk_application_new(NULL, 0);

    g_signal_connect(platform->app, "activate", G_CALLBACK(on_activate), NULL);
  } else {
    platform->app = fx_main_app->platform->app;

    g_object_ref(platform->app);
  }

  platform->on_launch = NULL;
  platform->on_terminate = NULL;

  *result = platform;

  return 0;
}

int
fx_platform_destroy (fx_platform_t *platform) {
  g_object_unref(platform->app);

  free(platform);

  return 0;
}

int
fx_on_platform_launch (fx_platform_t *platform, fx_launch_cb cb) {
  platform->on_launch = cb;

  return 0;
}

int
fx_on_platform_terminate (fx_platform_t *platform, fx_terminate_cb cb) {
  platform->on_terminate = cb;

  return 0;
}

int
fx_on_platform_suspend (fx_platform_t *platform, fx_suspend_cb cb) {
  return 0;
}

int
fx_on_platform_resume (fx_platform_t *platform, fx_resume_cb cb) {
  return 0;
}

int
fx_platform_run (fx_platform_t *platform) {
  g_application_run(G_APPLICATION(platform->app), 0, NULL);

  return 0;
}

int
fx_platform_terminate (fx_platform_t *platform) {
  g_application_quit(G_APPLICATION(platform->app));

  return 0;
}

static int
on_dispatch (void *data) {
  fx_dispatch_t *dispatch = (fx_dispatch_t *) data;

  dispatch->cb(fx_main_app, dispatch->data);

  free(dispatch);

  return 0;
}

int
fx_dispatch (fx_dispatch_cb cb, void *data) {
  fx_dispatch_t *dispatch = malloc(sizeof(fx_dispatch_t));

  dispatch->cb = cb;
  dispatch->data = data;

  g_idle_add(on_dispatch, dispatch);

  return 0;
}
