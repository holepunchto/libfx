#include "../../include/fx.h"
#include "winui.h"

struct fx_text_input_s {
  fx_node_t node;

  TextBox handle;

  struct {
    float x;
    float y;
    float width;
    float height;
  } bounds;

  void *data;

  fx_text_input_change_cb on_change;
};
