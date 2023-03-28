#include "../../include/fx.h"

struct fx_web_view_s {
  fx_node_t node;

  void *data;

  fx_web_view_message_cb on_message;
};
