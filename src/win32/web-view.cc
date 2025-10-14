#include "web-view.h"

#include "../../include/fx.h"
#include "../shared/bridge/edge/bridge.h"
#include "shared.h"
#include "winui.h"

static inline fire_and_forget
fx_web_view_init_bridge(fx_web_view_t *web_view, hstring bridge) noexcept {
  co_await web_view->handle.EnsureCoreWebView2Async();

  auto core_web_view = web_view->handle.CoreWebView2();

  co_await core_web_view.AddScriptToExecuteOnDocumentCreatedAsync(bridge);

  core_web_view.WebMessageReceived([=](const auto &sender, const auto &args) {
    if (web_view->on_message == NULL) return;

    auto message = args.WebMessageAsJson();

    auto str_len = fx__from_hstring(message, NULL, 0);

    auto str = new char[str_len];

    fx__from_hstring(message, str, str_len);

    web_view->on_message(web_view, str, str_len);

    delete[] str;
  });
}

extern "C" int
fx_web_view_init(fx_t *app, float x, float y, float width, float height, fx_web_view_t **result) {
  int err;

  hstring wstr;
  err = fx__to_hstring((char *) edge_bridge_js, edge_bridge_js_len, wstr);
  if (err < 0) return err;

  auto web_view = new fx_web_view_t();

  web_view->node.type = fx_web_view_node;

  web_view->handle.Width(width);
  web_view->handle.Height(height);

  web_view->bounds.x = x;
  web_view->bounds.y = y;
  web_view->bounds.width = width;
  web_view->bounds.height = height;

  web_view->data = NULL;

  web_view->on_message = NULL;

  *result = web_view;

  fx_web_view_init_bridge(web_view, wstr);

  return 0;
}

extern "C" int
fx_web_view_destroy(fx_web_view_t *web_view) {
  web_view->handle.Close();

  delete web_view;

  return 0;
}

extern "C" int
fx_on_web_view_message(fx_web_view_t *web_view, fx_web_view_message_cb cb) {
  web_view->on_message = cb;

  return 0;
}

extern "C" int
fx_get_web_view_data(fx_web_view_t *web_view, void **result) {
  *result = web_view->data;

  return 0;
}

extern "C" int
fx_set_web_view_data(fx_web_view_t *web_view, void *data) {
  web_view->data = data;

  return 0;
}

extern "C" int
fx_get_web_view_bounds(fx_web_view_t *web_view, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

extern "C" int
fx_set_web_view_bounds(fx_web_view_t *web_view, float x, float y, float width, float height) {
  return 0;
}

static inline fire_and_forget
fx_web_view_post_message(fx_web_view_t *web_view, hstring message) noexcept {
  co_await web_view->handle.EnsureCoreWebView2Async();

  web_view->handle.CoreWebView2().PostWebMessageAsJson(message);
}

extern "C" int
fx_web_view_post_message(fx_web_view_t *web_view, const char *message, size_t len) {
  int err;

  hstring wstr;
  err = fx__to_hstring(message, len, wstr);
  if (err < 0) return err;

  fx_web_view_post_message(web_view, wstr);

  return 0;
}

static inline fire_and_forget
fx_web_view_load_url(fx_web_view_t *web_view, hstring url) noexcept {
  co_await web_view->handle.EnsureCoreWebView2Async();

  web_view->handle.CoreWebView2().Navigate(url);
}

extern "C" int
fx_web_view_load_url(fx_web_view_t *web_view, const char *url, size_t len) {
  int err;

  hstring wstr;
  err = fx__to_hstring(url, len, wstr);
  if (err < 0) return err;

  fx_web_view_load_url(web_view, wstr);

  return 0;
}

static inline fire_and_forget
fx_web_view_load_html(fx_web_view_t *web_view, hstring html) noexcept {
  co_await web_view->handle.EnsureCoreWebView2Async();

  web_view->handle.CoreWebView2().NavigateToString(html);
}

extern "C" int
fx_web_view_load_html(fx_web_view_t *web_view, const char *html, size_t len) {
  int err;

  hstring wstr;
  err = fx__to_hstring(html, len, wstr);
  if (err < 0) return err;

  fx_web_view_load_html(web_view, wstr);

  return 0;
}
