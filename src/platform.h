#ifndef FX_PLATFORM_H
#define FX_PLATFORM_H

#include "../include/fx.h"
#include "message-queue.h"

fx_message_queue_t *
fx__get_message_queue (fx_t *app);

void
fx__read_start (fx_t *receiver, fx_message_cb cb);

void
fx__read_stop (fx_t *receiver);

#endif // FX_PLATFORM_H
