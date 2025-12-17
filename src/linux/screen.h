#ifndef FX_LINUX_SCREEN_H
#define FX_LINUX_SCREEN_H

#include "../../include/fx.h"

#include <gdk/gdk.h>

struct fx_screen_s {
  float x;
  float y;
  float width;
  float height;
};

#endif // FX_LINUX_SCREEN_H
