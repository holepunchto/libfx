#include <uv.h>

#include <WebView2.h> // Must be included after uv.h

#include "../../include/fx.h"

struct fx_web_view_s {
  fx_node_t node;

  HWND handle;

  ICoreWebView2Controller *controller;

  void *data;

  fx_web_view_ready_cb on_ready;
  fx_web_view_message_cb on_message;
};
