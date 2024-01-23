#include "../../include/fx.h"

#include <gtk/gtk.h>

struct fx_platform_s {
  GtkApplication *app;

  fx_launch_cb on_launch;
  fx_terminate_cb on_terminate;
};
