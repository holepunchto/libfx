#include "../../include/fx.h"

struct fx_image_s {
  fx_node_t node;

  HWND handle;

  HDC device_context;

  HBITMAP bitmap;

  void *data;
};
