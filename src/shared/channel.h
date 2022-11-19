#ifndef FX_CHANNEL_H
#define FX_CHANNEL_H

#include <stdbool.h>
#include <stdint.h>
#include <uv.h>

#include "../../include/fx.h"

typedef struct fx_channel_s fx_channel_t;
typedef struct fx_message_s fx_message_t;

typedef void (*fx_channel_notify_cb)(fx_channel_t *channel);

struct fx_channel_s {
  fx_t *app;
  uv_mutex_t lock;
  uv_async_t notify;
  bool paused;
  uint32_t capacity;
  uint32_t size;
  uint32_t back;
  uint32_t front;
  fx_message_t *messages;
  fx_channel_notify_cb on_notify;
};

struct fx_message_s {
  fx_t *sender;
  uv_buf_t message;
};

int
fx_channel_init (fx_t *app, fx_channel_t *channel, uint32_t capacity, fx_channel_notify_cb cb);

int
fx_channel_destroy (fx_channel_t *channel);

int
fx_channel_pop (fx_channel_t *channel, fx_t **sender, uv_buf_t *message);

int
fx_channel_push (fx_channel_t *channel, fx_t *sender, const uv_buf_t *message);

void
fx_channel_pause (fx_channel_t *channel);

void
fx_channel_resume (fx_channel_t *channel);

#endif // FX_CHANNEL_H
