#ifndef FX_H
#define FX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <uv.h>

typedef struct fx_s fx_t;

typedef void (*fx_launch_cb)(fx_t *app);
typedef void (*fx_dispatch_cb)(fx_t *receiver, void *data);
typedef void (*fx_terminate_cb)(fx_t *app);
typedef void (*fx_message_cb)(fx_t *receiver, const uv_buf_t *message, fx_t *sender);

int
fx_init (uv_loop_t *loop, fx_t **result);

int
fx_destroy (fx_t *app);

int
fx_run (fx_t *app);

int
fx_terminate (fx_t *app);

bool
fx_is_main (fx_t *app);

bool
fx_is_worker (fx_t *app);

int
fx_dispatch (fx_dispatch_cb cb, void *data);

int
fx_on_launch (fx_t *app, fx_launch_cb cb);

int
fx_on_terminate (fx_t *app, fx_terminate_cb cb);

int
fx_get_data (fx_t *app, void **result);

int
fx_set_data (fx_t *app, void *data);

int
fx_broadcast (fx_t *sender, const uv_buf_t *message);

int
fx_read_start (fx_t *receiver, fx_message_cb cb);

int
fx_read_stop (fx_t *receiver);

#include "fx/image.h"
#include "fx/node.h"
#include "fx/screen.h"
#include "fx/scroll-view.h"
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
