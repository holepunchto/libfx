#pragma once

#include <winrt/base.h>

#undef GetCurrentTime

#include <winrt/windows.foundation.collections.h>
#include <winrt/windows.foundation.h>
#include <winrt/windows.graphics.h>
#include <winrt/windows.media.core.h>
#include <winrt/windows.media.h>
#include <winrt/windows.storage.streams.h>

// UI headers for WinUI, which replace the deprecated system UI headers
// from the windows.ui.* namespace.

#include <winrt/microsoft.ui.dispatching.h>
#include <winrt/microsoft.ui.interop.h>
#include <winrt/microsoft.ui.windowing.h>
#include <winrt/microsoft.ui.xaml.controls.h>
#include <winrt/microsoft.ui.xaml.controls.primitives.h>
#include <winrt/microsoft.ui.xaml.documents.h>
#include <winrt/microsoft.ui.xaml.h>
#include <winrt/microsoft.ui.xaml.media.h>
#include <winrt/microsoft.ui.xaml.media.imaging.h>

using namespace winrt;

using namespace Windows::Foundation;
using namespace Windows::Graphics;
using namespace Windows::Media;
using namespace Windows::Media::Core;
using namespace Windows::Storage::Streams;

using namespace Microsoft::UI;
using namespace Microsoft::UI::Dispatching;
using namespace Microsoft::UI::Windowing;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Documents;
using namespace Microsoft::UI::Xaml::Media;
using namespace Microsoft::UI::Xaml::Media::Imaging;

#include <mddbootstrap.h>

#include <windowsappsdk-versioninfo.h>
