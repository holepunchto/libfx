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

struct fx_app : public ApplicationT<fx_app> {
  fx_platform_t *platform;

  fx_app(fx_platform_t *platform) : platform(platform) {}

  void
  OnLaunched (LaunchActivatedEventArgs const &) {
    if (platform->on_launch) platform->on_launch(fx_main_app);
  }

  void
  Exit () {
    ApplicationT<fx_app>::Exit();

    if (platform->on_terminate) platform->on_terminate(fx_main_app);
  }
};

static inline void
on_dispatch (MSG msg) {
  auto cb = reinterpret_cast<fx_dispatch_cb>(msg.wParam);
  auto data = reinterpret_cast<void *>(msg.lParam);

  cb(fx_main_app, data);
}

extern "C" int
fx_platform_init (fx_t *app, fx_platform_t **result) {
  HRESULT res;

  res = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

  if (FAILED(res)) return -1;

  const UINT32 version{WINDOWSAPPSDK_RELEASE_MAJORMINOR};

  PCWSTR version_tag{WINDOWSAPPSDK_RELEASE_VERSION_TAG_W};

  const PACKAGE_VERSION min_version{WINDOWSAPPSDK_RUNTIME_VERSION_UINT64};

  res = MddBootstrapInitialize(version, version_tag, min_version);

  if (FAILED(res)) return -1;

  auto platform = new fx_platform_t();

  platform->active_windows = 0;

  platform->on_launch = NULL;
  platform->on_terminate = NULL;

  *result = platform;

  return 0;
}

extern "C" int
fx_platform_destroy (fx_platform_t *platform) {
  MddBootstrapShutdown();

  CoUninitialize();

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
  fx_main_thread_id = GetCurrentThreadId();

  Application::Start([platform] (auto &&) { make<fx_app>(platform); });

  return 0;
}

extern "C" int
fx_dispatch (fx_dispatch_cb cb, void *data) {
  assert(fx_main_thread_id);

  auto success = PostThreadMessage(fx_main_thread_id, fx_msg_dispatch, (WPARAM) cb, (LPARAM) data);

  return success ? 0 : -1;
}
