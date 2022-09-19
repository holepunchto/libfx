cmake_minimum_required(VERSION 3.22)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

project(fx C)

if(APPLE)
  enable_language(OBJC)
endif()

add_subdirectory(vendor/libuv EXCLUDE_FROM_ALL)

add_library(fx OBJECT)

set_target_properties(
  fx
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE 1
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
)

if(IOS)
  target_sources(
    fx
    PRIVATE
      src/darwin/uikit/fx.m
      src/darwin/uikit/image.m
      src/darwin/uikit/node.m
      src/darwin/uikit/screen.m
      src/darwin/uikit/text.m
      src/darwin/uikit/text-input.m
      src/darwin/uikit/video.m
      src/darwin/uikit/view.m
      src/darwin/uikit/window.m
  )
elseif(APPLE)
  target_sources(
    fx
    PRIVATE
      src/darwin/appkit/fx.m
      src/darwin/appkit/image.m
      src/darwin/appkit/node.m
      src/darwin/appkit/screen.m
      src/darwin/appkit/text.m
      src/darwin/appkit/text-input.m
      src/darwin/appkit/video.m
      src/darwin/appkit/view.m
      src/darwin/appkit/window.m
  )
endif()

target_include_directories(
  fx
  PUBLIC
    include
    $<TARGET_PROPERTY:uv,INCLUDE_DIRECTORIES>
)

add_library(fx_shared SHARED $<TARGET_OBJECTS:fx>)

set_target_properties(
  fx_shared
  PROPERTIES
  OUTPUT_NAME fx
)

target_link_libraries(
  fx_shared
  PUBLIC
    uv
)

if(IOS)
  target_link_libraries(
    fx_shared
    PUBLIC
      "-framework Foundation"
      "-framework UIKit"
      "-framework AVFoundation"
      "-framework AVKit"
  )
elseif(APPLE)
  target_link_libraries(
    fx_shared
    PUBLIC
      "-framework Foundation"
      "-framework AppKit"
      "-framework AVFoundation"
      "-framework AVKit"
  )
endif()

add_library(fx_static STATIC $<TARGET_OBJECTS:fx>)

set_target_properties(
  fx_static
  PROPERTIES
  OUTPUT_NAME fx
)

target_link_libraries(
  fx_static
  PUBLIC
    uv
)

if(IOS)
  target_link_libraries(
    fx_static
    PUBLIC
      "-framework Foundation"
      "-framework UIKit"
      "-framework AVFoundation"
      "-framework AVKit"
  )
elseif(APPLE)
  target_link_libraries(
    fx_static
    PUBLIC
      "-framework Foundation"
      "-framework AppKit"
      "-framework AVFoundation"
      "-framework AVKit"
  )
endif()

install(TARGETS fx_shared fx_static)

install(FILES include/fx.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()
  add_subdirectory(test)

  add_subdirectory(example/ios EXCLUDE_FROM_ALL)
  add_subdirectory(example/macos EXCLUDE_FROM_ALL)
endif()
