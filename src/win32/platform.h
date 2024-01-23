#pragma once

#include "../../include/fx.h"
#include "../shared/platform.h"
#include "winui.h"

static DispatcherQueue *fx_dispatcher;

struct FX : public ApplicationT<FX, IXamlMetadataProvider> {
  FX();

  void
  OnLaunched (LaunchActivatedEventArgs const &);

  IXamlType
  GetXamlType (hstring const &name);

  IXamlType
  GetXamlType (TypeName const &type);

  com_array<XmlnsDefinition>
  GetXmlnsDefinitions ();

private:
  DispatcherQueue dispatcher;
  XamlControlsXamlMetaDataProvider provider;
};

struct fx_platform_s {
  fx_launch_cb on_launch;
  fx_terminate_cb on_terminate;
};
