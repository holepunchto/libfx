#include <assert.h>
#include <uv.h>

#include "../../include/fx.h"
#include "../shared/fx.h"
#include "fx.h"
#include "winui.h"

enum {
  fx_msg_dispatch = WM_APP + 1,
} fx_msg_t;

static DWORD fx_main_thread_id = 0;

static inline void
on_dispatch (MSG msg) {
  auto cb = reinterpret_cast<fx_dispatch_cb>(msg.wParam);
  auto data = reinterpret_cast<void *>(msg.lParam);

  cb(fx_main_app, data);
}

extern "C" int
fx_platform_init (fx_t *app, fx_platform_t **result) {
  auto platform = new fx_platform_t();

  platform->active_windows = 0;

  platform->on_launch = NULL;
  platform->on_terminate = NULL;

  *result = platform;

  return 0;
}

extern "C" int
fx_platform_destroy (fx_platform_t *platform) {
  delete platform;

  return 0;
}

extern "C" int
fx_on_platform_launch (fx_platform_t *platform, fx_launch_cb cb) {
  platform->on_launch = cb;

  return 0;
}

extern "C" int
fx_on_platform_terminate (fx_platform_t *platform, fx_terminate_cb cb) {
  platform->on_terminate = cb;

  return 0;
}

extern "C" int
fx_on_platform_suspend (fx_platform_t *platform, fx_suspend_cb cb) {
  return 0;
}

extern "C" int
fx_on_platform_resume (fx_platform_t *platform, fx_resume_cb cb) {
  return 0;
}

extern "C" int
fx_platform_run (fx_platform_t *platform) {
  HRESULT res;

  res = CoInitialize(NULL);

  if (FAILED(res)) return -1;

  fx_main_thread_id = GetCurrentThreadId();

  if (platform->on_launch) platform->on_launch(fx_main_app);

  MSG msg;
  BOOL success;

  while (success = GetMessage(&msg, NULL, 0, 0), success != 0) {
    if (success == -1) {
      // TODO: Figure out error handling.
    } else if (msg.hwnd) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    } else {
      switch (msg.message) {
      case fx_msg_dispatch:
        on_dispatch(msg);
        break;
      }
    }
  }

  if (platform->on_terminate) platform->on_terminate(fx_main_app);

  CoUninitialize();

  return 0;
}

extern "C" int
fx_dispatch (fx_dispatch_cb cb, void *data) {
  assert(fx_main_thread_id);

  auto success = PostThreadMessage(fx_main_thread_id, fx_msg_dispatch, (WPARAM) cb, (LPARAM) data);

  return success ? 0 : -1;
}
