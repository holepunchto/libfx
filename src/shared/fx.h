#ifndef FX_SHARED_H
#define FX_SHARED_H

#include <uv.h>

#include "../../include/fx.h"
#include "channel.h"
#include "platform.h"

static fx_t *fx_main_app;

struct fx_s {
  uv_loop_t *loop;

  void *data;

  fx_launch_cb on_launch;
  fx_terminate_cb on_terminate;
  fx_message_cb on_message;

  fx_channel_t messages;

  fx_platform_t *platform;
};

#endif // FX_SHARED_H
