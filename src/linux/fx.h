#include <gtk/gtk.h>

#include "../../include/fx.h"

struct fx_platform_s {
  GtkApplication *app;

  fx_launch_cb on_launch;
  fx_terminate_cb on_terminate;
};
