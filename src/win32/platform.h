#include "../../include/fx.h"

struct fx_platform_s {
  fx_launch_cb on_launch;
  fx_terminate_cb on_terminate;
};
