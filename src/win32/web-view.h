#pragma once

#include "../../include/fx.h"
#include "winui.h"

struct fx_web_view_s {
  fx_node_t node;

  WebView2 handle;

  IAsyncAction initialize;
  IAsyncAction navigate;

  struct {
    float x;
    float y;
    float width;
    float height;
  } bounds;

  void *data;

  fx_web_view_message_cb on_message;
};
