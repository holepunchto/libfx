#include "platform.h"

#include "../../include/fx.h"
#include "../shared/fx.h"

#include <gtk/gtk.h>
#include <stdlib.h>

static void
on_activate (GtkApplication *gtk, gpointer data) {
  fx_t *app = fx_main_app;

  if (app->platform->on_launch) app->platform->on_launch(app);
}

int
fx_platform_init (fx_t *app, fx_platform_t **result) {
  fx_platform_t *platform = malloc(sizeof(fx_platform_t));

  platform->app = gtk_application_new(NULL, 0);

  g_signal_connect(platform->app, "activate", G_CALLBACK(on_activate), NULL);

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
