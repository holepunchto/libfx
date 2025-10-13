#include "fx.h"

#include "../../include/fx.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <uv.h>

fx_t *fx_main_app = NULL;

static void
fx_add_worker(fx_t *worker) {
  uv_mutex_lock(&fx_main_app->lock);

  fx_worker_t *node = malloc(sizeof(fx_worker_t));

  node->worker = worker;
  node->next = fx_main_app->workers;

  fx_main_app->workers = node;

  uv_mutex_unlock(&fx_main_app->lock);
}

static void
fx_remove_worker(fx_t *worker) {
  uv_mutex_lock(&fx_main_app->lock);

  fx_worker_t *next = fx_main_app->workers;
  fx_worker_t *previous = NULL;

  while (next) {
    if (worker == next->worker) {
      if (previous) previous->next = next->next;
      else fx_main_app->workers = next->next;

      free(next);
      break;
    }

    previous = next;
    next = next->next;
  }

  uv_mutex_unlock(&fx_main_app->lock);
}

static void
on_message(fx_channel_t *channel) {
  fx_t *app = channel->app;

  for (;;) {
    fx_t *sender;
    uv_buf_t message;

    int err = fx_channel_read(channel, &sender, &message);
    if (err < 0) break;

    if (app->on_message) app->on_message(app, &message, sender);

    free(message.base);
  }
}

int
fx_init(uv_loop_t *loop, fx_t **result) {
  int err;

  fx_t *app = malloc(sizeof(fx_t));

  app->loop = loop;
  app->data = NULL;
  app->workers = NULL;

  app->on_message = NULL;

  if (fx_main_app == NULL) {
    fx_main_app = app;

    err = fx_platform_init(app, &app->platform);
    assert(err == 0);
  } else {
    fx_add_worker(app);

    app->platform = fx_main_app->platform;
  }

  err = uv_mutex_init_recursive(&app->lock);
  assert(err == 0);

  err = fx_channel_init(app, &app->messages, 1024, on_message);
  assert(err == 0);

  *result = app;

  return err;
}

static void
on_close(fx_channel_t *channel) {
  free(channel->app);
}

int
fx_destroy(fx_t *app) {
  if (fx_is_main(app)) {
    fx_main_app = NULL;

    fx_worker_t *next = app->workers;

    while (next) {
      fx_worker_t *worker = next;
      next = next->next;

      free(worker);
    }

    fx_platform_destroy(app->platform);
  } else {
    fx_remove_worker(app);
  }

  fx_channel_close(&app->messages, on_close);

  return 0;
}

bool
fx_is_main(fx_t *app) {
  return app == fx_main_app;
}

bool
fx_is_worker(fx_t *app) {
  return app != fx_main_app;
}

int
fx_on_suspend(fx_t *app, fx_suspend_cb cb) {
  app->on_suspend = cb;

  return 0;
}

int
fx_on_resume(fx_t *app, fx_resume_cb cb) {
  app->on_resume = cb;

  return 0;
}

int
fx_get_data(fx_t *app, void **result) {
  *result = app->data;

  return 0;
}

int
fx_set_data(fx_t *app, void *data) {
  app->data = data;

  return 0;
}

int
fx_broadcast(fx_t *sender, const uv_buf_t *message) {
  uv_mutex_lock(&fx_main_app->lock);

  if (fx_is_worker(sender)) {
    fx_channel_write(&fx_main_app->messages, sender, message);
  }

  fx_worker_t *next = sender->workers;

  while (next) {
    fx_t *receiver = next->worker;
    next = next->next;

    if (sender == receiver) continue;

    fx_channel_write(&receiver->messages, sender, message);
  }

  uv_mutex_unlock(&fx_main_app->lock);

  return 0;
}

int
fx_read_start(fx_t *receiver, fx_message_cb cb) {
  receiver->on_message = cb;

  fx_channel_resume(&receiver->messages);

  return 0;
}

int
fx_read_stop(fx_t *receiver) {
  receiver->on_message = NULL;

  fx_channel_pause(&receiver->messages);

  return 0;
}
