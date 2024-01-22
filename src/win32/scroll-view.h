#include "../../include/fx.h"
#include "winui.h"

struct fx_scroll_view_s {
  fx_node_t node;

  ScrollView handle;

  fx_view_t *view;

  struct {
    float x;
    float y;
    float width;
    float height;
  } bounds;

  void *data;
};
