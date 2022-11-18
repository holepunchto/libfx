#include <assert.h>
#include <stdlib.h>
#include <uv.h>

#include "../include/fx.h"
#include "message-queue.h"

static void
on_notify (uv_async_t *async) {
  fx_message_queue_t *queue = (fx_message_queue_t *) async->data;

  if (!queue->paused) queue->on_notify(queue);
}

static void
on_notify_dispatch (fx_t *app, void *data) {
  fx_message_queue_t *queue = (fx_message_queue_t *) data;

  if (!queue->paused) queue->on_notify(queue);
}

int
fx_message_queue_init (uv_loop_t *loop, fx_t *app, fx_message_queue_t *queue, uint32_t capacity, fx_message_queue_notify_cb cb) {
  queue->app = app;
  queue->capacity = capacity;
  queue->size = 0;
  queue->back = 0;
  queue->front = 0;
  queue->on_notify = cb;
  queue->notify.data = (void *) queue;

  int err;

  err = uv_mutex_init_recursive(&queue->lock);
  assert(err == 0);

  err = uv_cond_init(&queue->available);
  assert(err == 0);

  if (!fx_is_main(app)) {
    err = uv_async_init(loop, &queue->notify, on_notify);
    assert(err == 0);
  }

  queue->messages = calloc(capacity, sizeof(fx_message_t *));

  return 0;
}

static void
on_close (uv_handle_t *handle) {
}

int
fx_message_queue_destroy (fx_message_queue_t *queue) {
  uv_mutex_destroy(&queue->lock);

  uv_cond_destroy(&queue->available);

  if (!fx_is_main(queue->app)) {
    uv_close((uv_handle_t *) &queue->notify, on_close);
  }

  free(queue->messages);

  return 0;
}

fx_message_t *
fx_message_queue_pop (fx_message_queue_t *queue) {
  uv_mutex_lock(&queue->lock);

  if (queue->size >= queue->capacity) {
    uv_cond_signal(&queue->available);
  }

  fx_message_t *req = NULL;

  if (queue->size > 0) {
    queue->size--;

    req = queue->messages[queue->back++];

    if (queue->back >= queue->capacity) {
      queue->back = 0;
    }
  }

  uv_mutex_unlock(&queue->lock);

  return req;
}

void
fx_message_queue_push (fx_message_queue_t *queue, fx_message_t *req) {
  uv_mutex_lock(&queue->lock);

  if (queue->size >= queue->capacity) {
    uv_cond_wait(&queue->available, &queue->lock);
  }

  queue->size++;

  queue->messages[queue->front++] = req;

  if (queue->front >= queue->capacity) {
    queue->front = 0;
  }

  uv_mutex_unlock(&queue->lock);

  if (fx_is_main(queue->app)) {
    fx_dispatch(on_notify_dispatch, (void *) queue);
  } else {
    uv_async_send(&queue->notify);
  }
}

void
fx_message_queue_pause (fx_message_queue_t *queue) {
  queue->paused = true;

  uv_unref((uv_handle_t *) &queue->notify);
}

void
fx_message_queue_resume (fx_message_queue_t *queue) {
  queue->paused = false;

  uv_ref((uv_handle_t *) &queue->notify);
}
