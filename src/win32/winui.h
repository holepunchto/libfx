#pragma once

#include <winrt/base.h>

#undef GetCurrentTime

#include <winrt/windows.foundation.h>
#include <winrt/windows.foundation.collections.h>
#include <winrt/windows.media.h>
#include <winrt/windows.media.core.h>

// UI headers for WinUI, which replace the deprecated system UI headers
// from the windows.ui.* namespace.

#include <winrt/microsoft.ui.windowing.h>
#include <winrt/microsoft.ui.xaml.h>
#include <winrt/microsoft.ui.xaml.controls.h>
#include <winrt/microsoft.ui.xaml.controls.primitives.h>
#include <winrt/microsoft.ui.xaml.documents.h>

using namespace winrt;

using namespace Windows::Foundation;
using namespace Windows::Media;
using namespace Windows::Media::Core;

using namespace Microsoft::UI;
using namespace Microsoft::UI::Windowing;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Documents;

#include <mddbootstrap.h>

#include <windowsappsdk-versioninfo.h>
