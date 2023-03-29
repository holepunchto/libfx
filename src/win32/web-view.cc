#include <uv.h>

#include <wrl/event.h> // Must be included after uv.h

#include "../../include/fx.h"
#include "web-view.h"

using namespace Microsoft::WRL;

static const char *fx_web_view_class = "STATIC";

static inline int
fx_to_wstring (const char *str, int len, PWCHAR wstr) {
  len = MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len);

  if (len == 0) return uv_translate_sys_error(GetLastError());

  return len;
}

static inline void
fx_web_view_prepare (fx_web_view_t *web_view) {
  CreateCoreWebView2Environment(
    Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
      [=] (HRESULT res, ICoreWebView2Environment *env) noexcept -> HRESULT {
        env->AddRef();

        env->CreateCoreWebView2Controller(
          web_view->handle,
          Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
            [=] (HRESULT res, ICoreWebView2Controller *ctl) noexcept -> HRESULT {
              ctl->AddRef();

              RECT bounds;
              GetClientRect(web_view->handle, &bounds);

              ctl->put_Bounds(bounds);

              web_view->environment = env;
              web_view->controller = ctl;

              if (web_view->on_ready) web_view->on_ready(web_view, 0);

              return S_OK;
            }
          )
            .Get()
        );

        return S_OK;
      }
    )
      .Get()
  );
}

extern "C" int
fx_web_view_init (fx_t *app, float x, float y, float width, float height, fx_web_view_t **result) {
  HINSTANCE instance = GetModuleHandle(NULL);

  HWND handle = CreateWindowEx(
    0,
    fx_web_view_class,
    NULL,
    WS_VISIBLE | WS_CHILD,
    (int) x,
    (int) y,
    (int) width,
    (int) height,
    HWND_MESSAGE,
    NULL,
    instance,
    NULL
  );

  if (handle == NULL) return -1;

  fx_web_view_t *web_view = new fx_web_view_t();

  web_view->node.type = fx_web_view_node;

  web_view->handle = handle;

  web_view->data = NULL;

  web_view->on_ready = NULL;
  web_view->on_message = NULL;

  *result = web_view;

  fx_web_view_prepare(web_view);

  return 0;
}

extern "C" int
fx_web_view_destroy (fx_web_view_t *web_view) {
  delete web_view;

  return 0;
}

extern "C" int
fx_on_web_view_ready (fx_web_view_t *web_view, fx_web_view_ready_cb cb) {
  web_view->on_ready = cb;

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
fx_web_view_load_url (fx_web_view_t *web_view, const char *url, size_t _len) {
  ICoreWebView2 *view;

  web_view->controller->get_CoreWebView2(&view);

  int len = fx_to_wstring(url, 0, NULL);
  if (len < 0) return len;

  PWCHAR str = new WCHAR[len];

  int err = fx_to_wstring(url, len, str);
  if (err < 0) {
    delete[] str;
    return err;
  }

  view->Navigate(str);

  delete[] str;

  return 0;
}

extern "C" int
fx_web_view_load_html (fx_web_view_t *web_view, const char *html, size_t _len) {
  ICoreWebView2 *view;

  web_view->controller->get_CoreWebView2(&view);

  int len = fx_to_wstring(html, 0, NULL);
  if (len < 0) return len;

  PWCHAR str = new WCHAR[len];

  int err = fx_to_wstring(html, len, str);
  if (err < 0) {
    delete[] str;
    return err;
  }

  view->NavigateToString(str);

  delete[] str;

  return 0;
}
