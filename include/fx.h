#ifndef FX_H
#define FX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <uv.h>

typedef struct fx_s fx_t;
typedef struct fx_send_s fx_send_t;

typedef void (*fx_launch_cb)(fx_t *app);
typedef void (*fx_dispatch_cb)(fx_t *app, void *data);
typedef void (*fx_message_cb)(fx_t *app, void *message, fx_t *sender);
typedef void (*fx_delivered_cb)(fx_send_t *req);

struct fx_send_s {
  uv_async_t async;
  fx_t *app;
  void *message;
  fx_delivered_cb cb;
  void *data;
};

int
fx_init (uv_loop_t *loop, fx_t **result);

int
fx_destroy (fx_t *app);

int
fx_run (fx_t *app);

int
fx_stop (fx_t *app);

int
fx_terminate (fx_t *app);

bool
fx_is_main (fx_t *app);

int
fx_dispatch (fx_dispatch_cb cb, void *data);

int
fx_send (fx_t *app, fx_send_t *req, void *message, fx_delivered_cb cb);

int
fx_on_launch (fx_t *app, fx_launch_cb cb);

int
fx_on_message (fx_t *app, fx_message_cb cb);

int
fx_get_data (fx_t *app, void **result);

int
fx_set_data (fx_t *app, void *data);

#include "fx/image.h"
#include "fx/node.h"
#include "fx/screen.h"
#include "fx/text-input.h"
#include "fx/text.h"
#include "fx/video.h"
#include "fx/view.h"
#include "fx/web-view.h"
#include "fx/window.h"

#ifdef __cplusplus
}
#endif

#endif // FX_H
