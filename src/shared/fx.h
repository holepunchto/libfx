#ifndef FX_SHARED_H
#define FX_SHARED_H

#include <uv.h>

#include "../../include/fx.h"
#include "channel.h"
#include "platform.h"

typedef struct fx_worker_s fx_worker_t;

extern fx_t *fx_main_app;

struct fx_s {
  uv_loop_t *loop;
  uv_mutex_t lock;

  void *data;

  fx_message_cb on_message;

  fx_channel_t messages;

  fx_worker_t *workers;
  fx_platform_t *platform;
};

struct fx_worker_s {
  fx_t *worker;
  fx_worker_t *next;
};

#endif // FX_SHARED_H
