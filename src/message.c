#include <stdlib.h>
#include <uv.h>

#include "../include/fx.h"
#include "channel.h"
#include "platform.h"

typedef struct fx_listener_s fx_listener_t;

struct fx_listener_s {
  fx_t *receiver;
  fx_listener_t *next;
};

static fx_listener_t *listeners = NULL;

static uv_mutex_t listeners_lock;

static uv_once_t listeners_init = UV_ONCE_INIT;

static void
on_listeners_init () {
  uv_mutex_init_recursive(&listeners_lock);
}

int
fx_broadcast (fx_t *sender, const uv_buf_t *buf) {
  uv_once(&listeners_init, on_listeners_init);

  uv_mutex_lock(&listeners_lock);

  fx_listener_t *listener = listeners;

  while (listener) {
    fx_t *receiver = listener->receiver;
    listener = listener->next;

    if (receiver == sender) continue;

    fx_channel_t *messages = fx__get_channel(receiver);

    void *memory = malloc(sizeof(fx_message_t) + buf->len);

    fx_message_t *message = memory;

    message->sender = sender;
    message->buf.len = buf->len;
    message->buf.base = (char *) memory + sizeof(fx_message_t);

    memcpy(message->buf.base, buf->base, buf->len);

    fx_channel_push(messages, message);
  }

  uv_mutex_unlock(&listeners_lock);

  return 0;
}

int
fx_read_start (fx_t *receiver, fx_message_cb cb) {
  uv_once(&listeners_init, on_listeners_init);

  uv_mutex_lock(&listeners_lock);

  fx_listener_t *listener = malloc(sizeof(fx_listener_t));

  listener->receiver = receiver;
  listener->next = listeners;

  listeners = listener;

  uv_mutex_unlock(&listeners_lock);

  fx__read_start(receiver, cb);

  fx_channel_t *messages = fx__get_channel(receiver);
  fx_channel_resume(messages);

  return 0;
}

int
fx_read_stop (fx_t *receiver) {
  uv_once(&listeners_init, on_listeners_init);

  uv_mutex_lock(&listeners_lock);

  fx_listener_t *next = listeners;
  fx_listener_t *previous = NULL;

  while (next) {
    if (receiver == next->receiver) {
      if (previous) previous->next = next->next;
      else listeners = next->next;

      free(next);
      break;
    }

    previous = next;
    next = next->next;
  }

  uv_mutex_unlock(&listeners_lock);

  fx__read_stop(receiver);

  fx_channel_t *messages = fx__get_channel(receiver);
  fx_channel_pause(messages);

  return 0;
}
