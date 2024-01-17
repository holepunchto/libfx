#include "../../include/fx.h"
#include "winui.h"

struct fx_view_s {
  fx_node_t node;

  Canvas handle;

  void *data;
};
