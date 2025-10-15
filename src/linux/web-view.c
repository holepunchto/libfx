#include "web-view.h"

#include "../shared/bridge/webkit/bridge.h"

#include <stdlib.h>

static void
fx__on_web_view_message(WebKitUserContentManager *self, JSCValue *message, void *data) {
  fx_web_view_t *web_view = (fx_web_view_t *) data;

  GBytes *bytes = jsc_value_to_string_as_bytes(message);

  if (web_view->on_message) web_view->on_message(web_view, g_bytes_get_data(bytes, NULL), g_bytes_get_size(bytes));

  g_bytes_unref(bytes);
}

int
fx_web_view_init(fx_t *app, float x, float y, float width, float height, fx_web_view_t **result) {
  GtkWidget *handle = webkit_web_view_new();

  if (handle == NULL) return -1;

  fx_web_view_t *web_view = malloc(sizeof(fx_web_view_t));

  web_view->node.type = fx_web_view_node;

  web_view->handle = WEBKIT_WEB_VIEW(handle);

  web_view->data = NULL;

  web_view->on_message = NULL;

  web_view->bounds.x = x;
  web_view->bounds.y = y;
  web_view->bounds.width = width;
  web_view->bounds.height = height;

  *result = web_view;

  gtk_widget_set_visible(handle, true);

  gtk_widget_set_size_request(handle, width, height);

  gchar *source = g_strndup((const gchar *) webkit_bridge_js, webkit_bridge_js_len);

  WebKitUserScript *script = webkit_user_script_new(
    source,
    WEBKIT_USER_CONTENT_INJECT_ALL_FRAMES,
    WEBKIT_USER_SCRIPT_INJECT_AT_DOCUMENT_START,
    NULL,
    NULL
  );

  g_free(source);

  WebKitUserContentManager *user_content_manager = webkit_web_view_get_user_content_manager(web_view->handle);

  webkit_user_content_manager_add_script(user_content_manager, script);

  webkit_user_script_unref(script);

  g_signal_connect(G_OBJECT(user_content_manager), "script-message-received::bridge", G_CALLBACK(fx__on_web_view_message), web_view);

  webkit_user_content_manager_register_script_message_handler(user_content_manager, "bridge", NULL);

  return 0;
}

int
fx_web_view_destroy(fx_web_view_t *web_view) {
  free(web_view);

  return 0;
}

int
fx_on_web_view_message(fx_web_view_t *web_view, fx_web_view_message_cb cb) {
  web_view->on_message = cb;

  return 0;
}

int
fx_get_web_view_data(fx_web_view_t *web_view, void **result) {
  *result = web_view->data;

  return 0;
}

int
fx_set_web_view_data(fx_web_view_t *web_view, void *data) {
  web_view->data = data;

  return 0;
}

int
fx_get_web_view_bounds(fx_web_view_t *web_view, float *x, float *y, float *width, float *height) {
  if (x) *x = web_view->bounds.x;
  if (y) *y = web_view->bounds.y;
  if (width) *width = web_view->bounds.width;
  if (height) *height = web_view->bounds.height;

  return 0;
}

int
fx_set_web_view_bounds(fx_web_view_t *web_view, float x, float y, float width, float height) {
  web_view->bounds.x = x;
  web_view->bounds.y = y;
  web_view->bounds.width = width;
  web_view->bounds.height = height;

  return 0;
}

int
fx_web_view_post_message(fx_web_view_t *web_view, const char *message, size_t len) {
  gchar *js = g_strdup_printf("globalThis.bridge.dispatchMessage(%.*s)", (int) len, message);

  webkit_web_view_evaluate_javascript(web_view->handle, js, -1, NULL, NULL, NULL, NULL, NULL);

  g_free(js);

  return 0;
}

int
fx_web_view_load_url(fx_web_view_t *web_view, const char *url, size_t len) {
  webkit_web_view_load_uri(web_view->handle, url);

  return 0;
}

int
fx_web_view_load_html(fx_web_view_t *web_view, const char *html, size_t len) {
  webkit_web_view_load_html(web_view->handle, html, NULL);

  return 0;
}
