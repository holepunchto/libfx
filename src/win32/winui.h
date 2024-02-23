#pragma once

// Core WinRT headers.
// https://learn.microsoft.com/en-us/windows/win32/api/_winrt/

#include <winrt/base.h>

#undef GetCurrentTime

#include <winrt/windows.foundation.collections.h>
#include <winrt/windows.foundation.h>
#include <winrt/windows.graphics.h>
#include <winrt/windows.media.core.h>
#include <winrt/windows.media.h>
#include <winrt/windows.storage.streams.h>

// Headers for system UI interop APIs.
// https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/win32/_uiinterop/

#include <winrt/windows.ui.xaml.interop.h>

// Headers for WinUI, which replace the legacy system headers from the
// windows.ui.* namespace.
// https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/

#include <winrt/microsoft.ui.dispatching.h>
#include <winrt/microsoft.ui.interop.h>
#include <winrt/microsoft.ui.windowing.h>
#include <winrt/microsoft.ui.xaml.controls.h>
#include <winrt/microsoft.ui.xaml.controls.primitives.h>
#include <winrt/microsoft.ui.xaml.documents.h>
#include <winrt/microsoft.ui.xaml.h>
#include <winrt/microsoft.ui.xaml.markup.h>
#include <winrt/microsoft.ui.xaml.media.h>
#include <winrt/microsoft.ui.xaml.media.imaging.h>
#include <winrt/microsoft.ui.xaml.xamltypeinfo.h>
#include <winrt/microsoft.web.webview2.core.h>

using namespace winrt;

using namespace Windows::Foundation;
using namespace Windows::Graphics;
using namespace Windows::Media;
using namespace Windows::Media::Core;
using namespace Windows::Storage::Streams;

using namespace Windows::UI::Xaml::Interop;

using namespace Microsoft::UI;
using namespace Microsoft::UI::Dispatching;
using namespace Microsoft::UI::Windowing;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Documents;
using namespace Microsoft::UI::Xaml::Markup;
using namespace Microsoft::UI::Xaml::Media;
using namespace Microsoft::UI::Xaml::Media::Imaging;
using namespace Microsoft::UI::Xaml::XamlTypeInfo;
