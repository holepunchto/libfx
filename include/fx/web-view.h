#ifndef FX_WEB_VIEW_H
#define FX_WEB_VIEW_H

#include "../fx.h"

typedef struct fx_web_view_s fx_web_view_t;

int
fx_web_view_init (fx_t *app, double x, double y, double width, double height, fx_web_view_t **result);

int
fx_web_view_load_url (fx_web_view_t *web_view, const char *url, size_t len);

int
fx_web_view_load_html (fx_web_view_t *web_view, const char *html, size_t len);

#endif // FX_WEBVIEW_H
