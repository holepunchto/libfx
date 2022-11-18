#ifndef FX_MESSAGE_H
#define FX_MESSAGE_H

#include <uv.h>

#include "../fx.h"

typedef void (*fx_message_cb)(fx_t *receiver, const uv_buf_t *buf, fx_t *sender);

int
fx_broadcast (fx_t *sender, const uv_buf_t *buf);

int
fx_read_start (fx_t *receiver, fx_message_cb cb);

int
fx_read_stop (fx_t *receiver);

#endif // FX_MESSAGE_H
