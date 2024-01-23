#ifndef FX_LINUX_TEXT_INPUT_H
#define FX_LINUX_TEXT_INPUT_H

#include "../../include/fx.h"

struct fx_text_input_s {
  fx_node_t node;

  void *data;

  fx_text_input_change_cb on_change;
};

#endif // FX_LINUX_TEXT_INPUT_H
