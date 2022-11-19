#ifndef FX_PLATFORM_H
#define FX_PLATFORM_H

#include "../include/fx.h"
#include "channel.h"

fx_channel_t *
fx__get_channel (fx_t *app);

void
fx__read_start (fx_t *receiver, fx_message_cb cb);

void
fx__read_stop (fx_t *receiver);

#endif // FX_PLATFORM_H
