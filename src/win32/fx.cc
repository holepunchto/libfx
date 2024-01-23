#include "../../include/fx.h"

#include "../shared/fx.h"
#include "fx.h"
#include "winui.h"

#include <assert.h>
#include <uv.h>

static DispatcherQueue *fx_dispatcher;

struct fx : public ApplicationT<fx, IXamlMetadataProvider> {
  fx_platform_t *platform;

  fx(fx_platform_t *platform) : platform(platform) {}

  DispatcherQueue dispatcher = DispatcherQueue::GetForCurrentThread();

  void
  OnLaunched (LaunchActivatedEventArgs const &) {
    Resources().MergedDictionaries().Append(XamlControlsResources());

    fx_dispatcher = &dispatcher;

    if (platform->on_launch) platform->on_launch(fx_main_app);

    dispatcher.ShutdownCompleted([=] (const auto &sender, const auto &args) {
      if (platform->on_terminate) platform->on_terminate(fx_main_app);
    });
  }

  XamlControlsXamlMetaDataProvider provider;

  IXamlType
  GetXamlType (hstring const &name) {
    return provider.GetXamlType(name);
  }

  IXamlType
  GetXamlType (TypeName const &type) {
    return provider.GetXamlType(type);
  }

  com_array<XmlnsDefinition>
  GetXmlnsDefinitions () {
    return provider.GetXmlnsDefinitions();
  }
};

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
  Application::Start([=] (auto &&) { make<fx>(platform); });

  return 0;
}

extern "C" int
fx_dispatch (fx_dispatch_cb cb, void *data) {
  assert(fx_dispatcher);

  auto success = fx_dispatcher->TryEnqueue([=] () { cb(fx_main_app, data); });

  return success ? 0 : -1;
}
