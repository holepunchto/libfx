cmake_minimum_required(VERSION 3.22)

project(fx C)

if(APPLE)
  enable_language(OBJC)
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
      src/darwin/uikit/fx.h
      src/darwin/uikit/fx.m
      src/darwin/uikit/image.h
      src/darwin/uikit/image.m
      src/darwin/uikit/node.m
      src/darwin/uikit/screen.h
      src/darwin/uikit/screen.m
      src/darwin/uikit/scroll-view.h
      src/darwin/uikit/scroll-view.m
      src/darwin/uikit/text.h
      src/darwin/uikit/text.m
      src/darwin/uikit/text-input.h
      src/darwin/uikit/text-input.m
      src/darwin/uikit/video.h
      src/darwin/uikit/video.m
      src/darwin/uikit/view.h
      src/darwin/uikit/view.m
      src/darwin/uikit/web-view.h
      src/darwin/uikit/web-view.m
      src/darwin/uikit/window.h
      src/darwin/uikit/window.m
  )
elseif(APPLE)
  target_sources(
    fx
    PRIVATE
      src/darwin/appkit/fx.h
      src/darwin/appkit/fx.m
      src/darwin/appkit/image.h
      src/darwin/appkit/image.m
      src/darwin/appkit/node.m
      src/darwin/appkit/screen.h
      src/darwin/appkit/screen.m
      src/darwin/appkit/scroll-view.h
      src/darwin/appkit/scroll-view.m
      src/darwin/appkit/text.h
      src/darwin/appkit/text.m
      src/darwin/appkit/text-input.h
      src/darwin/appkit/text-input.m
      src/darwin/appkit/video.h
      src/darwin/appkit/video.m
      src/darwin/appkit/view.h
      src/darwin/appkit/view.m
      src/darwin/appkit/web-view.h
      src/darwin/appkit/web-view.m
      src/darwin/appkit/window.h
      src/darwin/appkit/window.m
  )
endif()

target_include_directories(
  fx
  PUBLIC
    include
    $<TARGET_PROPERTY:uv,INTERFACE_INCLUDE_DIRECTORIES>
)

if(IOS)
  target_link_libraries(
    fx
    PUBLIC
      "-framework Foundation"
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
      "-framework AppKit"
      "-framework AVFoundation"
      "-framework AVKit"
      "-framework WebKit"
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
    uv
    fx
)

add_library(fx_static STATIC)

set_target_properties(
  fx_static
  PROPERTIES
  OUTPUT_NAME fx
)

target_link_libraries(
  fx_static
  PUBLIC
    uv_a
    fx
)

install(TARGETS fx_shared fx_static)

install(FILES include/fx.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()
  add_subdirectory(test)

  add_subdirectory(example/ios EXCLUDE_FROM_ALL)
  add_subdirectory(example/macos EXCLUDE_FROM_ALL)
endif()
