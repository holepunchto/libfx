cmake_minimum_required(VERSION 3.22)

project(example_macos C OBJC)

add_executable(
  example_macos
  Info.plist
  ../main.c
)

set_target_properties(
  example_macos
  PROPERTIES
  MACOSX_BUNDLE YES
  MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/Info.plist"
  XCODE_ATTRIBUTE_PRODUCT_NAME "Example"
  XCODE_ATTRIBUTE_BUNDLE_IDENTIFIER "com.example.Example"
)

target_link_libraries(
  example_macos
  PRIVATE
    fx_static
)
