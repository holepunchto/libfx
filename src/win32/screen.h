#include "../../include/fx.h"

struct fx_screen_s {
  HMONITOR handle;

  int x;
  int y;
  int width;
  int height;

  float scale;
};
