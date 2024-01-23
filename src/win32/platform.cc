#include "platform.h"

#include "../../include/fx.h"
#include "../shared/fx.h"
#include "winui.h"

FX::FX() : dispatcher(DispatcherQueue::GetForCurrentThread()) {}

void
FX::OnLaunched(LaunchActivatedEventArgs const &) {
  Resources().MergedDictionaries().Append(XamlControlsResources());

  fx_dispatcher = &dispatcher;

  auto platform = fx_main_app->platform;

  if (platform->on_launch) platform->on_launch(fx_main_app);

  dispatcher.ShutdownCompleted([=] (const auto &sender, const auto &args) {
    if (platform->on_terminate) platform->on_terminate(fx_main_app);
  });
}

IXamlType
FX::GetXamlType(hstring const &name) {
  return provider.GetXamlType(name);
}

IXamlType
FX::GetXamlType(TypeName const &type) {
  return provider.GetXamlType(type);
}

com_array<XmlnsDefinition>
FX::GetXmlnsDefinitions() {
  return provider.GetXmlnsDefinitions();
}

extern "C" int
fx_platform_init (fx_t *app, fx_platform_t **result) {
  HRESULT res;

  res = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

  if (FAILED(res)) return -1;

  const UINT32 version = Release::MajorMinor;

  PCWSTR version_tag = Release::VersionTag;

  const PACKAGE_VERSION min_version{Runtime::Version::UInt64};

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
