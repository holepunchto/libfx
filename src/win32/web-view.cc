#include <assert.h>
#include <uv.h>

#include <wrl/event.h> // Must be included after uv.h

#include "../../include/fx.h"
#include "../shared/bridge/edge/bridge.h"
#include "web-view.h"

using namespace Microsoft::WRL;

static const char *fx_web_view_class = "STATIC";

static inline int
fx_to_wstring (const char *str, int str_len, PWCHAR wstr, int wstr_len) {
  wstr_len = MultiByteToWideChar(CP_UTF8, 0, str, str_len, wstr, wstr_len);

  if (wstr_len == 0) return uv_translate_sys_error(GetLastError());

  if (str_len != -1) {
    wstr_len += 1; /* NULL */

    if (wstr != NULL) wstr[wstr_len - 1] = L'\0';
  }

  return wstr_len;
}

static inline int
fx_to_string (PCWCHAR wstr, int wstr_len, char *str, int str_len) {
  str_len = WideCharToMultiByte(CP_UTF8, 0, wstr, wstr_len, str, str_len, NULL, NULL);

  if (str_len == 0) return uv_translate_sys_error(GetLastError());

  if (wstr_len != -1) {
    str_len += 1; /* NULL */

    if (str != NULL) str[str_len - 1] = '\0';
  }

  return str_len;
}

static inline void
fx_web_view_prepare (fx_web_view_t *web_view) {
  CreateCoreWebView2Environment(
    Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
      [=] (HRESULT res, ICoreWebView2Environment *env) noexcept -> HRESULT {
        env->CreateCoreWebView2Controller(
          web_view->handle,
          Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
            [=] (HRESULT res, ICoreWebView2Controller *ctl) noexcept -> HRESULT {
              ctl->AddRef();

              RECT bounds;
              GetClientRect(web_view->handle, &bounds);

              ctl->put_Bounds(bounds);

              web_view->controller = ctl;

              ICoreWebView2 *native_web_view;

              ctl->get_CoreWebView2(&native_web_view);

              int str_len = fx_to_wstring((char *) edge_bridge_js, edge_bridge_js_len, NULL, 0);
              assert(str_len > 0);

              PWCHAR str = new WCHAR[str_len];

              int err = fx_to_wstring((char *) edge_bridge_js, edge_bridge_js_len, str, str_len);
              assert(err > 0);

              native_web_view->AddScriptToExecuteOnDocumentCreated(
                str,
                Callback<ICoreWebView2AddScriptToExecuteOnDocumentCreatedCompletedHandler>(
                  [=] (HRESULT res, PCWSTR id) noexcept -> HRESULT {
                    delete[] str;

                    return S_OK;
                  }
                )
                  .Get()
              );

              EventRegistrationToken token;

              native_web_view->add_WebMessageReceived(
                Callback<ICoreWebView2WebMessageReceivedEventHandler>(
                  [=] (ICoreWebView2 *sender, ICoreWebView2WebMessageReceivedEventArgs *args) noexcept -> HRESULT {
                    LPWSTR message;

                    args->TryGetWebMessageAsString(&message);

                    int str_len = fx_to_string(message, -1, NULL, 0);
                    assert(str_len > 0);

                    char *str = new char[str_len];

                    int err = fx_to_string(message, -1, str, str_len);
                    assert(err > 0);

                    CoTaskMemFree(message);

                    if (web_view->on_message) web_view->on_message(web_view, str);

                    delete[] str;

                    return S_OK;
                  }
                )
                  .Get(),
                &token
              );

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
fx_web_view_init (fx_t *app, float x, float y, float width, float height, fx_web_view_ready_cb cb, fx_web_view_t **result) {
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

  web_view->controller = NULL;

  web_view->data = NULL;

  web_view->on_ready = cb;
  web_view->on_message = NULL;

  *result = web_view;

  fx_web_view_prepare(web_view);

  return 0;
}

extern "C" int
fx_web_view_destroy (fx_web_view_t *web_view) {
  web_view->controller->Close();

  web_view->controller->Release();

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
  ICoreWebView2 *view;

  web_view->controller->get_CoreWebView2(&view);

  int str_len = fx_to_wstring(message, -1, NULL, 0);
  if (str_len < 0) return str_len;

  PWCHAR str = new WCHAR[str_len];

  int err = fx_to_wstring(message, -1, str, str_len);
  if (err < 0) {
    delete[] str;
    return err;
  }

  HRESULT res = view->PostWebMessageAsJson(str);

  delete[] str;

  return FAILED(res) ? -1 : 0;
}

extern "C" int
fx_web_view_load_url (fx_web_view_t *web_view, const char *url, size_t len) {
  ICoreWebView2 *view;

  web_view->controller->get_CoreWebView2(&view);

  int str_len = fx_to_wstring(url, len, NULL, 0);
  if (str_len < 0) return str_len;

  PWCHAR str = new WCHAR[str_len];

  int err = fx_to_wstring(url, len, str, str_len);
  if (err < 0) {
    delete[] str;
    return err;
  }

  HRESULT res = view->Navigate(str);

  delete[] str;

  return FAILED(res) ? -1 : 0;
}

extern "C" int
fx_web_view_load_html (fx_web_view_t *web_view, const char *html, size_t len) {
  ICoreWebView2 *view;

  web_view->controller->get_CoreWebView2(&view);

  int str_len = fx_to_wstring(html, len, NULL, 0);
  if (str_len < 0) return str_len;

  PWCHAR str = new WCHAR[str_len];

  int err = fx_to_wstring(html, len, str, str_len);
  if (err < 0) {
    delete[] str;
    return err;
  }

  HRESULT res = view->NavigateToString(str);

  delete[] str;

  return FAILED(res) ? -1 : 0;
}
