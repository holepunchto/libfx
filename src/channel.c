#include <assert.h>
#include <stdlib.h>
#include <uv.h>

#include "../include/fx.h"
#include "channel.h"

static void
on_notify (uv_async_t *async) {
  fx_channel_t *channel = (fx_channel_t *) async->data;

  if (!channel->paused) channel->on_notify(channel);
}

static void
on_notify_dispatch (fx_t *app, void *data) {
  fx_channel_t *channel = (fx_channel_t *) data;

  if (!channel->paused) channel->on_notify(channel);
}

int
fx_channel_init (uv_loop_t *loop, fx_t *app, fx_channel_t *channel, uint32_t capacity, fx_channel_notify_cb cb) {
  channel->app = app;
  channel->capacity = capacity;
  channel->size = 0;
  channel->back = 0;
  channel->front = 0;
  channel->on_notify = cb;
  channel->notify.data = (void *) channel;

  int err;

  err = uv_mutex_init_recursive(&channel->lock);
  assert(err == 0);

  err = uv_cond_init(&channel->available);
  assert(err == 0);

  if (!fx_is_main(app)) {
    err = uv_async_init(loop, &channel->notify, on_notify);
    assert(err == 0);
  }

  channel->messages = calloc(capacity, sizeof(fx_message_t *));

  return 0;
}

static void
on_close (uv_handle_t *handle) {
}

int
fx_channel_destroy (fx_channel_t *channel) {
  uv_mutex_destroy(&channel->lock);

  uv_cond_destroy(&channel->available);

  if (!fx_is_main(channel->app)) {
    uv_close((uv_handle_t *) &channel->notify, on_close);
  }

  free(channel->messages);

  return 0;
}

fx_message_t *
fx_channel_pop (fx_channel_t *channel) {
  uv_mutex_lock(&channel->lock);

  if (channel->size >= channel->capacity) {
    uv_cond_signal(&channel->available);
  }

  fx_message_t *req = NULL;

  if (channel->size > 0) {
    channel->size--;

    req = channel->messages[channel->back++];

    if (channel->back >= channel->capacity) {
      channel->back = 0;
    }
  }

  uv_mutex_unlock(&channel->lock);

  return req;
}

void
fx_channel_push (fx_channel_t *channel, fx_message_t *req) {
  uv_mutex_lock(&channel->lock);

  if (channel->size >= channel->capacity) {
    uv_cond_wait(&channel->available, &channel->lock);
  }

  channel->size++;

  channel->messages[channel->front++] = req;

  if (channel->front >= channel->capacity) {
    channel->front = 0;
  }

  uv_mutex_unlock(&channel->lock);

  if (fx_is_main(channel->app)) {
    fx_dispatch(on_notify_dispatch, (void *) channel);
  } else {
    uv_async_send(&channel->notify);
  }
}

void
fx_channel_pause (fx_channel_t *channel) {
  channel->paused = true;

  uv_unref((uv_handle_t *) &channel->notify);
}

void
fx_channel_resume (fx_channel_t *channel) {
  channel->paused = false;

  uv_ref((uv_handle_t *) &channel->notify);
}
