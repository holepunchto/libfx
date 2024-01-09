#include "../../include/fx.h"

struct fx_image_s {
  fx_node_t node;

  HWND handle;

  HBITMAP bitmap;

  void *data;
};
