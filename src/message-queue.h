#ifndef FX_MESSAGE_QUEUE_H
#define FX_MESSAGE_QUEUE_H

#include <stdbool.h>
#include <stdint.h>
#include <uv.h>

#include "../include/fx.h"

typedef struct fx_message_queue_s fx_message_queue_t;
typedef struct fx_message_s fx_message_t;

typedef void (*fx_message_queue_notify_cb)(fx_message_queue_t *queue);

struct fx_message_queue_s {
  fx_t *app;
  uv_mutex_t lock;
  uv_cond_t available;
  uv_async_t notify;
  bool paused;
  uint32_t capacity;
  uint32_t size;
  uint32_t back;
  uint32_t front;
  fx_message_t **messages;
  fx_message_queue_notify_cb on_notify;
};

struct fx_message_s {
  fx_t *sender;
  uv_buf_t buf;
};

int
fx_message_queue_init (uv_loop_t *loop, fx_t *app, fx_message_queue_t *queue, uint32_t capacity, fx_message_queue_notify_cb cb);

int
fx_message_queue_destroy (fx_message_queue_t *queue);

fx_message_t *
fx_message_queue_pop (fx_message_queue_t *queue);

void
fx_message_queue_push (fx_message_queue_t *queue, fx_message_t *message);

void
fx_message_queue_pause (fx_message_queue_t *queue);

void
fx_message_queue_resume (fx_message_queue_t *queue);

#endif // FX_MESSAGE_QUEUE_H
