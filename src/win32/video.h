#include "../../include/fx.h"
#include "winui.h"

struct fx_video_s {
  fx_node_t node;

  MediaPlayerElement handle;

  struct {
    float x;
    float y;
    float width;
    float height;
  } bounds;

  void *data;
};
