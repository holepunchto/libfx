#include <assert.h>
#include <uv.h>

#include <wrl/event.h> // Must be included after uv.h

#include "../../include/fx.h"
#include "../shared/bridge/edge/bridge.h"
#include "web-view.h"
#include "shared.h"

using namespace Microsoft::WRL;

static const char *fx_web_view_class = "STATIC";

static inline void
fx_web_view_prepare (fx_web_view_t *web_view, const char *data_directory) {
  int err;

  WCHAR wdata_directory[MAX_PATH];

  err = fx__to_wstring(data_directory, -1, wdata_directory, MAX_PATH);
  assert(err >= 0);

  CreateCoreWebView2EnvironmentWithOptions(
    NULL,
    wdata_directory,
    NULL,
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

              int str_len = fx__to_wstring((char *) edge_bridge_js, edge_bridge_js_len, NULL, 0);
              assert(str_len > 0);

              PWCHAR str = new WCHAR[str_len];

              int err = fx__to_wstring((char *) edge_bridge_js, edge_bridge_js_len, str, str_len);
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

                    int str_len = fx__to_string(message, -1, NULL, 0);
                    assert(str_len > 0);

                    auto str = new char[str_len];

                    int err = fx__to_string(message, -1, str, str_len);
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
fx_web_view_init (fx_t *app, const char *data_directory, float x, float y, float width, float height, fx_web_view_ready_cb cb, fx_web_view_t **result) {
  auto instance = GetModuleHandle(NULL);

  auto handle = CreateWindowEx(
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

  auto web_view = new fx_web_view_t();

  web_view->node.type = fx_web_view_node;

  web_view->handle = handle;

  web_view->controller = NULL;

  web_view->data = NULL;

  web_view->on_ready = cb;
  web_view->on_message = NULL;

  *result = web_view;

  fx_web_view_prepare(web_view, data_directory);

  return 0;
}

extern "C" int
fx_web_view_destroy (fx_web_view_t *web_view) {
  web_view->controller->Close();

  web_view->controller->Release();

  DestroyWindow(web_view->handle);

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
  auto success = SetWindowPos(web_view->handle, NULL, (int) x, (int) y, (int) width, (int) height, 0);

  if (!success) return -1;

  if (web_view->controller) {
    RECT rect;

    rect.top = x;
    rect.left = y;
    rect.right = x + width;
    rect.bottom = y + height;

    web_view->controller->put_Bounds(rect);
  }

  return 0;
}

extern "C" int
fx_web_view_post_message (fx_web_view_t *web_view, const char *message) {
  ICoreWebView2 *view;

  web_view->controller->get_CoreWebView2(&view);

  int str_len = fx__to_wstring(message, -1, NULL, 0);
  if (str_len < 0) return str_len;

  auto str = new WCHAR[str_len];

  int err = fx__to_wstring(message, -1, str, str_len);
  if (err < 0) {
    delete[] str;
    return err;
  }

  auto res = view->PostWebMessageAsJson(str);

  delete[] str;

  return FAILED(res) ? -1 : 0;
}

extern "C" int
fx_web_view_load_url (fx_web_view_t *web_view, const char *url, size_t len) {
  ICoreWebView2 *view;

  web_view->controller->get_CoreWebView2(&view);

  int str_len = fx__to_wstring(url, len, NULL, 0);
  if (str_len < 0) return str_len;

  auto str = new WCHAR[str_len];

  int err = fx__to_wstring(url, len, str, str_len);
  if (err < 0) {
    delete[] str;
    return err;
  }

  auto res = view->Navigate(str);

  delete[] str;

  return FAILED(res) ? -1 : 0;
}

extern "C" int
fx_web_view_load_html (fx_web_view_t *web_view, const char *html, size_t len) {
  ICoreWebView2 *view;

  web_view->controller->get_CoreWebView2(&view);

  int str_len = fx__to_wstring(html, len, NULL, 0);
  if (str_len < 0) return str_len;

  auto str = new WCHAR[str_len];

  int err = fx__to_wstring(html, len, str, str_len);
  if (err < 0) {
    delete[] str;
    return err;
  }

  auto res = view->NavigateToString(str);

  delete[] str;

  return FAILED(res) ? -1 : 0;
}
