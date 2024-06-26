#pragma once

#include "../../include/fx.h"
#include "winui.h"

struct fx_view_s {
  fx_node_t node;

  Canvas handle;

  struct {
    float x;
    float y;
    float width;
    float height;
  } bounds;

  void *data;
};
