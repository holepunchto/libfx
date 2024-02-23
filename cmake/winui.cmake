include(ExternalProject)

ExternalProject_Add(
  CppWinRT
  URL "https://www.nuget.org/api/v2/package/Microsoft.Windows.CppWinRT/2.0.240111.5"

  CONFIGURE_COMMAND ""

  BUILD_COMMAND
    "<SOURCE_DIR>/bin/cppwinrt.exe" -in local -output "<BINARY_DIR>/include"
  COMMAND
    ${CMAKE_COMMAND}
    -E copy
    "<SOURCE_DIR>/bin/cppwinrt.exe"
    "<BINARY_DIR>/cppwinrt.exe"

  INSTALL_COMMAND ""

  EXCLUDE_FROM_ALL
)

ExternalProject_Get_property(CppWinRT BINARY_DIR)

add_executable(cppwinrt IMPORTED GLOBAL)

add_dependencies(cppwinrt CppWinRT)

set_target_properties(
  cppwinrt
  PROPERTIES
  IMPORTED_LOCATION "${BINARY_DIR}/cppwinrt.exe"
)

# Make sure our C++/WinRT headers take precendence over the system provided
# Windows SDK headers.
include_directories(BEFORE SYSTEM "${BINARY_DIR}/include")

ExternalProject_Add(
  WindowsAppSDK
  URL "https://www.nuget.org/api/v2/package/Microsoft.WindowsAppSDK/1.4.231219000"

  CONFIGURE_COMMAND ""

  BUILD_COMMAND
    cppwinrt
    -ref sdk
    -in "<SOURCE_DIR>/lib/uap10.0"
    -in "<SOURCE_DIR>/lib/uap10.0.17763"
    -in "<SOURCE_DIR>/lib/uap10.0.18362"
    -output "<BINARY_DIR>/include"

  INSTALL_COMMAND ""

  EXCLUDE_FROM_ALL
)

ExternalProject_Get_property(WindowsAppSDK SOURCE_DIR)

add_library(windowsappsdk INTERFACE)

add_dependencies(windowsappsdk WindowsAppSDK)

target_include_directories(
  windowsappsdk
  INTERFACE
    "${SOURCE_DIR}/include"
    "${BINARY_DIR}/include"
)
