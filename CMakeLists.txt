cmake_minimum_required(VERSION 3.25)

project(fx C)

if(APPLE)
  enable_language(OBJC)
endif()

if(WIN32)
  enable_language(CXX)
endif()

if(NOT TARGET uv)
  add_subdirectory(vendor/libuv EXCLUDE_FROM_ALL)
endif()

add_library(fx OBJECT)

set_target_properties(
  fx
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE ON
)

if(APPLE)
  set_target_properties(
    fx
    PROPERTIES
    OBJC_STANDARD 99
  )
endif()

if(WIN32)
  set_target_properties(
    fx
    PROPERTIES
    CXX_STANDARD 20
  )
endif()

target_sources(
  fx
  INTERFACE
    include/fx.h
    include/fx/image.h
    include/fx/node.h
    include/fx/screen.h
    include/fx/scroll-view.h
    include/fx/text.h
    include/fx/text-input.h
    include/fx/video.h
    include/fx/web-view.h
    include/fx/window.h
  PRIVATE
    src/shared/channel.c
    src/shared/channel.h
    src/shared/fx.c
    src/shared/fx.h
    src/shared/platform.h
)

if(IOS)
  target_sources(
    fx
    PRIVATE
      src/ios/fx.h
      src/ios/fx.m
      src/ios/image.h
      src/ios/image.m
      src/ios/node.m
      src/ios/screen.h
      src/ios/screen.m
      src/ios/scroll-view.h
      src/ios/scroll-view.m
      src/ios/text.h
      src/ios/text.m
      src/ios/text-input.h
      src/ios/text-input.m
      src/ios/video.h
      src/ios/video.m
      src/ios/view.h
      src/ios/view.m
      src/ios/web-view.h
      src/ios/web-view.m
      src/ios/window.h
      src/ios/window.m
  )
elseif(APPLE)
  target_sources(
    fx
    PRIVATE
      src/darwin/fx.h
      src/darwin/fx.m
      src/darwin/image.h
      src/darwin/image.m
      src/darwin/node.m
      src/darwin/screen.h
      src/darwin/screen.m
      src/darwin/scroll-view.h
      src/darwin/scroll-view.m
      src/darwin/text.h
      src/darwin/text.m
      src/darwin/text-input.h
      src/darwin/text-input.m
      src/darwin/video.h
      src/darwin/video.m
      src/darwin/view.h
      src/darwin/view.m
      src/darwin/web-view.h
      src/darwin/web-view.m
      src/darwin/window.h
      src/darwin/window.m
  )
endif()

if(WIN32)
  target_sources(
    fx
    PRIVATE
      src/win32/fx.cc
      src/win32/fx.h
      src/win32/image.cc
      src/win32/image.h
      src/win32/node.cc
      src/win32/scroll-view.cc
      src/win32/scroll-view.h
      src/win32/shared.h
      src/win32/text.cc
      src/win32/text.h
      src/win32/text-input.cc
      src/win32/text-input.h
      src/win32/video.cc
      src/win32/video.h
      src/win32/view.cc
      src/win32/view.h
      src/win32/web-view.cc
      src/win32/web-view.h
      src/win32/window.cc
      src/win32/window.h
      src/win32/winui.h
  )
endif()

if(LINUX)
  target_sources(
    fx
    PRIVATE
      src/linux/fx.c
      src/linux/fx.h
      src/linux/image.c
      src/linux/image.h
      src/linux/node.c
      src/linux/scroll-view.c
      src/linux/scroll-view.h
      src/linux/text.c
      src/linux/text.h
      src/linux/text-input.c
      src/linux/text-input.h
      src/linux/video.c
      src/linux/video.h
      src/linux/view.c
      src/linux/view.h
      src/linux/web-view.c
      src/linux/web-view.h
      src/linux/window.c
      src/linux/window.h
  )
endif()

target_include_directories(
  fx
  PUBLIC
    include
    $<TARGET_PROPERTY:uv,INTERFACE_INCLUDE_DIRECTORIES>
)

if(WIN32)
  target_include_directories(
    fx
    PUBLIC
      src/win32/webview2/include
  )

  target_link_directories(
    fx
    PUBLIC
      src/win32/webview2/${CMAKE_LIBRARY_ARCHITECTURE}
  )
endif()

if(IOS)
  target_link_libraries(
    fx
    PUBLIC
      "-framework Foundation"
      "-framework CoreMedia"
      "-framework UIKit"
      "-framework AVFoundation"
      "-framework AVKit"
      "-framework WebKit"
  )
elseif(APPLE)
  target_link_libraries(
    fx
    PUBLIC
      "-framework Foundation"
      "-framework CoreMedia"
      "-framework AppKit"
      "-framework AVFoundation"
      "-framework AVKit"
      "-framework WebKit"
  )
endif()

if(WIN32)
  target_link_libraries(
    fx
    PRIVATE
      WindowsApp.lib
    PUBLIC
      WebView2LoaderStatic.lib
  )
endif()

if(LINUX)
  find_package(PkgConfig REQUIRED)

  pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

  target_link_libraries(
    fx
    PUBLIC
      PkgConfig::GTK4
  )
endif()

add_library(fx_shared SHARED)

set_target_properties(
  fx_shared
  PROPERTIES
  OUTPUT_NAME fx
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_link_libraries(
  fx_shared
  PUBLIC
    fx
    uv
)

add_library(fx_static STATIC)

set_target_properties(
  fx_static
  PROPERTIES
  OUTPUT_NAME fx
  PREFIX lib
)

target_link_libraries(
  fx_static
  PUBLIC
    fx
    uv_a
)

install(TARGETS fx_shared fx_static)

install(FILES include/fx.h DESTINATION include)

install(DIRECTORY include/fx DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()

  add_subdirectory(test)
  add_subdirectory(example)
endif()
