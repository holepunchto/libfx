#include <uv.h>

#include "../include/fx.h"

static uv_thread_t thread;

static fx_t *parent;
static fx_t *child;

static uv_buf_t buf;

static void
on_parent_message (fx_t *receiver, const uv_buf_t *buf, fx_t *sender) {
  printf("message to parent\n");

  fx_broadcast(parent, buf);

  fx_read_stop(parent);
}

static void
on_child_message (fx_t *receiver, const uv_buf_t *buf, fx_t *sender) {
  printf("message to child\n");

  fx_read_stop(child);
}

static void
on_thread (void *data) {
  uv_loop_t loop;
  uv_loop_init(&loop);

  fx_init(&loop, &child);

  fx_read_start(child, on_child_message);

  fx_broadcast(child, &buf);

  uv_run(&loop, UV_RUN_DEFAULT);

  fx_terminate(parent);
}

int
main () {
  fx_init(uv_default_loop(), &parent);

  fx_read_start(parent, on_parent_message);

  buf = uv_buf_init("hello world", 11);

  uv_thread_create(&thread, on_thread, NULL);

  return fx_run(parent);
}
