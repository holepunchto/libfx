#include "../../include/fx.h"

struct fx_platform_s {
  fx_launch_cb on_launch;
  fx_terminate_cb on_terminate;
  fx_suspend_cb on_suspend;
  fx_resume_cb on_resume;
};
