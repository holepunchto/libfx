#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <uv.h>

#include "../../include/fx.h"
#include "fx.h"

static void
on_message (fx_channel_t *channel) {
  fx_t *app = channel->app;
  fx_message_t *message;

  for (;;) {
    fx_t *sender;
    uv_buf_t message;

    int err = fx_channel_pop(channel, &sender, &message);
    if (err < 0) break;

    if (app->on_message) app->on_message(app, &message, sender);

    free(message.base);
  }
}

int
fx_init (uv_loop_t *loop, fx_t **result) {
  fx_t *app = malloc(sizeof(fx_t));

  if (fx_main_app == NULL) fx_main_app = app;

  app->loop = loop;

  app->data = NULL;

  app->on_launch = NULL;
  app->on_message = NULL;
  app->on_terminate = NULL;

  int err;

  err = fx_channel_init(app, &app->messages, 1024, on_message);
  assert(err == 0);

  err = fx_platform_init(app, &app->platform);
  assert(err == 0);

  *result = app;

  return 0;
}

int
fx_destroy (fx_t *app) {
  if (fx_is_main(app)) fx_main_app = NULL;

  fx_platform_destroy(app->platform);

  free(app);

  return 0;
}

bool
fx_is_main (fx_t *app) {
  return app == fx_main_app;
}

bool
fx_is_worker (fx_t *app) {
  return app != fx_main_app;
}

int
fx_on_launch (fx_t *app, fx_launch_cb cb) {
  app->on_launch = cb;

  return 0;
}

int
fx_on_terminate (fx_t *app, fx_terminate_cb cb) {
  app->on_terminate = cb;

  return 0;
}

int
fx_get_data (fx_t *app, void **result) {
  *result = app->data;

  return 0;
}

int
fx_set_data (fx_t *app, void *data) {
  app->data = data;

  return 0;
}

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
fx_broadcast (fx_t *sender, const uv_buf_t *message) {
  uv_once(&listeners_init, on_listeners_init);

  uv_mutex_lock(&listeners_lock);

  fx_listener_t *listener = listeners;

  while (listener) {
    fx_t *receiver = listener->receiver;
    listener = listener->next;

    if (receiver == sender) continue;

    fx_channel_t *messages = &receiver->messages;
    fx_channel_push(messages, sender, message);
  }

  uv_mutex_unlock(&listeners_lock);

  return 0;
}

int
fx_read_start (fx_t *receiver, fx_message_cb cb) {
  receiver->on_message = cb;

  uv_once(&listeners_init, on_listeners_init);

  uv_mutex_lock(&listeners_lock);

  fx_listener_t *listener = malloc(sizeof(fx_listener_t));

  listener->receiver = receiver;
  listener->next = listeners;

  listeners = listener;

  uv_mutex_unlock(&listeners_lock);

  fx_channel_t *messages = &receiver->messages;
  fx_channel_resume(messages);

  return 0;
}

int
fx_read_stop (fx_t *receiver) {
  receiver->on_message = NULL;

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

  fx_channel_t *messages = &receiver->messages;
  fx_channel_pause(messages);

  return 0;
}
