include_guard(GLOBAL)

declare_port(
  "https://webkitgtk.org/releases/webkitgtk-2.50.1.tar.xz"
  webkitgtk
  BYPRODUCTS lib/libwebkitgtk.so
  ARGS
    -DPORT=GTK
    -DUSE_LIBDRM=OFF
    -DUSE_LIBSECRET=OFF
    -DUSE_JPEGXL=OFF
    -DUSE_LIBHYPHEN=OFF
    -DUSE_AVIF=OFF
    -DUSE_LCMS=OFF
    -DUSE_LIBBACKTRACE=OFF
    -DENABLE_BUBBLEWRAP_SANDBOX=OFF
    -DENABLE_JOURNALD_LOG=OFF
    -DENABLE_GAMEPAD=OFF
    -DENABLE_DOCUMENTATION=OFF
    -DENABLE_SPEECH_SYNTHESIS=OFF
    -DENABLE_SPELLCHECK=OFF
)

add_library(webkitgtk STATIC IMPORTED GLOBAL)

add_dependencies(webkitgtk  ${webkitgtk})

set_target_properties(
  webkitgtk
  PROPERTIES
  IMPORTED_LOCATION "${webkitgtk_PREFIX}/lib/libwebkitgtk.so"
)

file(MAKE_DIRECTORY "${webkitgtk_PREFIX}/include")

target_include_directories(
  webkitgtk
  INTERFACE "${webkitgtk_PREFIX}/include"
)
