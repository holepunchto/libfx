#ifndef FX_LINUX_WEB_VIEW_H
#define FX_LINUX_WEB_VIEW_H

#include "../../include/fx.h"

#include <webkit/webkit.h>

struct fx_web_view_s {
  fx_node_t node;

  WebKitWebView *handle;

  struct {
    float x;
    float y;
    float width;
    float height;
  } bounds;

  void *data;

  fx_web_view_message_cb on_message;
};

#endif // FX_LINUX_WEB_VIEW_H
