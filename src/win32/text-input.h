#include "../../include/fx.h"

struct fx_text_input_s {
  fx_node_t node;

  HWND handle;

  void *data;

  fx_text_input_change_cb on_change;
};
