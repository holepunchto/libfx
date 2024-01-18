#include "../../include/fx.h"
#include "winui.h"

struct fx_video_s {
  fx_node_t node;

  MediaPlayerElement handle;

  void *data;
};
