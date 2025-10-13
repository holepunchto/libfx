#include "channel.h"

#include "../../include/fx.h"
#include "fx.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

static void
on_notify(uv_async_t *async) {
  fx_channel_t *channel = (fx_channel_t *) async->data;

  if (!channel->paused) channel->on_notify(channel);
}

static void
on_notify_dispatch(fx_t *app, void *data) {
  fx_channel_t *channel = (fx_channel_t *) data;

  if (!channel->paused) channel->on_notify(channel);
}

int
fx_channel_init(fx_t *app, fx_channel_t *channel, uint32_t capacity, fx_channel_notify_cb cb) {
  int err;

  channel->app = app;
  channel->capacity = capacity;
  channel->size = 0;
  channel->back = 0;
  channel->front = 0;
  channel->on_notify = cb;
  channel->notify.data = (void *) channel;

  err = uv_mutex_init_recursive(&channel->lock);
  assert(err == 0);

  err = uv_async_init(app->loop, &channel->notify, on_notify);
  assert(err == 0);

  channel->messages = calloc(capacity, sizeof(fx_message_t));

  return err;
}

static void
on_close(uv_handle_t *handle) {
  fx_channel_t *channel = (fx_channel_t *) handle->data;

  if (channel->on_close) channel->on_close(channel);
}

int
fx_channel_close(fx_channel_t *channel, fx_channel_close_cb cb) {
  channel->on_close = cb;

  uv_mutex_destroy(&channel->lock);

  uv_close((uv_handle_t *) &channel->notify, on_close);

  free(channel->messages);

  return 0;
}

int
fx_channel_read(fx_channel_t *channel, fx_t **sender, uv_buf_t *message) {
  uv_mutex_lock(&channel->lock);

  if (channel->size == 0) {
    uv_mutex_unlock(&channel->lock);

    return -1;
  }

  channel->size--;

  fx_message_t *back = &channel->messages[channel->back++];

  *sender = back->sender;
  *message = back->message;

  if (channel->back >= channel->capacity) {
    channel->back = 0;
  }

  uv_mutex_unlock(&channel->lock);

  return 0;
}

int
fx_channel_write(fx_channel_t *channel, fx_t *sender, const uv_buf_t *message) {
  int err;

  uv_mutex_lock(&channel->lock);

  if (channel->size >= channel->capacity) {
    uv_mutex_unlock(&channel->lock);

    return -1;
  }

  channel->size++;

  fx_message_t *front = &channel->messages[channel->front++];

  front->sender = sender;
  front->message.len = message->len;
  front->message.base = malloc(message->len);

  memcpy(front->message.base, message->base, message->len);

  if (channel->front >= channel->capacity) {
    channel->front = 0;
  }

  if (fx_is_main(channel->app)) {
    err = fx_dispatch(on_notify_dispatch, (void *) channel);
    assert(err == 0);
  } else {
    err = uv_async_send(&channel->notify);
    assert(err == 0);
  }

  uv_mutex_unlock(&channel->lock);

  return 0;
}

void
fx_channel_pause(fx_channel_t *channel) {
  channel->paused = true;

  uv_unref((uv_handle_t *) &channel->notify);
}

void
fx_channel_resume(fx_channel_t *channel) {
  channel->paused = false;

  uv_ref((uv_handle_t *) &channel->notify);
}
