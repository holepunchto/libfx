#include "../../include/fx.h"
#include "winui.h"

struct fx_text_s {
  fx_node_t node;

  TextBlock handle;

  void *data;
};

struct fx_text_span_s {
  uint32_t start;
  uint32_t end;
};
