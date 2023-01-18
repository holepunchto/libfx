#ifndef FX_WEB_VIEW_H
#define FX_WEB_VIEW_H

#include "../fx.h"

typedef struct fx_web_view_s fx_web_view_t;

typedef void (*fx_web_view_message_cb)(fx_web_view_t *web_view, const char *message);

int
fx_web_view_init (fx_t *app, float x, float y, float width, float height, fx_web_view_t **result);

int
fx_web_view_destroy (fx_web_view_t *web_view);

int
fx_on_web_view_message (fx_web_view_t *web_view, fx_web_view_message_cb cb);

int
fx_get_web_view_data (fx_web_view_t *web_view, void **result);

int
fx_set_web_view_data (fx_web_view_t *web_view, void *data);

int
fx_get_web_view_bounds (fx_web_view_t *web_view, float *x, float *y, float *width, float *height);

int
fx_set_web_view_bounds (fx_web_view_t *web_view, float x, float y, float width, float height);

int
fx_web_view_post_message (fx_web_view_t *web_view, const char *message);

int
fx_web_view_load_url (fx_web_view_t *web_view, const char *url, size_t len);

int
fx_web_view_load_html (fx_web_view_t *web_view, const char *html, size_t len);

#endif // FX_WEBVIEW_H
