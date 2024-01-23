#ifndef FX_LINUX_SCREEN_H
#define FX_LINUX_SCREEN_H

#include "../../include/fx.h"

#include <gdk/gdk.h>

struct fx_screen_s {
  GdkMonitor *monitor;
};

#endif // FX_LINUX_SCREEN_H
