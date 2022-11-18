#include "../../platform.h"
#include "fx.h"

fx_message_queue_t *
fx__get_message_queue (fx_t *app) {
  return &app->messages;
}

void
fx__read_start (fx_t *receiver, fx_message_cb cb) {
  receiver->on_message = cb;
}

void
fx__read_stop (fx_t *receiver) {
  receiver->on_message = NULL;
}
