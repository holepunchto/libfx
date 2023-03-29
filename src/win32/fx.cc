#include "../../include/fx.h"
#include "../shared/fx.h"
#include "fx.h"

extern "C" int
fx_platform_init (fx_t *app, fx_platform_t **result) {
  fx_platform_t *platform = new fx_platform_t();

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
  HRESULT res = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

  if (FAILED(res)) return -1;

  if (platform->on_launch) platform->on_launch(fx_main_app);

  MSG msg;
  BOOL success;

  while (success = GetMessage(&msg, NULL, 0, 0), success != 0) {
    if (success == -1) {
      // TODO: Figure out error handling.
    } else {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return 0;
}

extern "C" int
fx_platform_terminate (fx_platform_t *platform) {
  PostQuitMessage(0);

  return 0;
}

extern "C" int
fx_dispatch (fx_dispatch_cb cb, void *data) {
  return 0;
}
