#include "web-view.h"
#include "../../include/fx.h"
#include "../shared/bridge/edge/bridge.h"
#include "shared.h"
#include "winui.h"

extern "C" int
fx_web_view_init (fx_t *app, float x, float y, float width, float height, fx_web_view_t **result) {
  auto web_view = new fx_web_view_t();

  web_view->node.type = fx_web_view_node;

  web_view->handle.Width(width);
  web_view->handle.Height(height);

  web_view->data = NULL;

  web_view->on_message = NULL;

  *result = web_view;

  return 0;
}

extern "C" int
fx_web_view_destroy (fx_web_view_t *web_view) {
  delete web_view;

  return 0;
}

extern "C" int
fx_on_web_view_message (fx_web_view_t *web_view, fx_web_view_message_cb cb) {
  web_view->on_message = cb;

  return 0;
}

extern "C" int
fx_get_web_view_data (fx_web_view_t *web_view, void **result) {
  *result = web_view->data;

  return 0;
}

extern "C" int
fx_set_web_view_data (fx_web_view_t *web_view, void *data) {
  web_view->data = data;

  return 0;
}

extern "C" int
fx_get_web_view_bounds (fx_web_view_t *web_view, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

extern "C" int
fx_set_web_view_bounds (fx_web_view_t *web_view, float x, float y, float width, float height) {
  return 0;
}

extern "C" int
fx_web_view_post_message (fx_web_view_t *web_view, const char *message) {
  return 0;
}

extern "C" int
fx_web_view_load_url (fx_web_view_t *web_view, const char *url, size_t len) {
  auto wstr_len = fx__to_wstring(url, len, NULL, 0);

  auto wstr = new wchar_t[wstr_len];

  fx__to_wstring(url, len, wstr, wstr_len);

  Uri uri(wstr);

  delete[] wstr;

  web_view->handle.Source(uri);

  return 0;
}

extern "C" int
fx_web_view_load_html (fx_web_view_t *web_view, const char *html, size_t len) {
  auto wstr_len = fx__to_wstring(html, len, NULL, 0);

  auto wstr = new wchar_t[wstr_len];

  fx__to_wstring(html, len, wstr, wstr_len);

  web_view->handle.NavigateToString(wstr);

  delete[] wstr;

  return 0;
}
