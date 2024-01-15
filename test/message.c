#include <assert.h>
#include <uv.h>

#include "../include/fx.h"

static uv_thread_t thread;

static fx_t *parent;
static fx_t *child;

static uv_buf_t buf;

static void
on_parent_message (fx_t *receiver, const uv_buf_t *buf, fx_t *sender) {
  int e;

  printf("message to parent\n");

  e = fx_broadcast(parent, buf);
  assert(e == 0);

  e = fx_read_stop(parent);
  assert(e == 0);
}

static void
on_child_message (fx_t *receiver, const uv_buf_t *buf, fx_t *sender) {
  int e;

  printf("message to child\n");

  e = fx_read_stop(child);
  assert(e == 0);
}

static void
on_thread (void *data) {
  int e;

  uv_loop_t loop;
  e = uv_loop_init(&loop);
  assert(e == 0);

  e = fx_init(&loop, &child);
  assert(e == 0);

  e = fx_read_start(child, on_child_message);
  assert(e == 0);

  e = fx_broadcast(child, &buf);
  assert(e == 0);

  e = uv_run(&loop, UV_RUN_DEFAULT);
  assert(e == 0);

  e = fx_terminate(parent);
  assert(e == 0);
}

int
main () {
  int e;

  e = fx_init(uv_default_loop(), &parent);
  assert(e == 0);

  e = fx_read_start(parent, on_parent_message);
  assert(e == 0);

  buf = uv_buf_init("hello world", 11);

  e = uv_thread_create(&thread, on_thread, NULL);
  assert(e == 0);

  return fx_run(parent);
}
