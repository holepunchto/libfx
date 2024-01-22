list(APPEND tests
  # Core

  message

  # Components

  image/basic

  scroll-view/basic

  text/basic
  text/used-bounds

  text-input/basic

  video/basic
  video/no-controls
  video/no-controls-loop

  web-view/basic
  web-view/message

  window/basic
  window/destroy-on-close
  window/multiple
  window/no-frame
  window/no-resize
  window/screen-center
  window/screen-size
  window/title
)

foreach(test IN LISTS tests)
  string(REPLACE "/" "_" name ${test})

  add_executable(${name} ${test}.c)

  target_link_libraries(
    ${name}
    PRIVATE
      fx_static
  )

  add_test(
    NAME ${name}
    COMMAND ${name}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

  set_tests_properties(
    ${name}
    PROPERTIES
    TIMEOUT 30
  )

  add_custom_command(
    TARGET ${name}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${name}> $<TARGET_RUNTIME_DLLS:${name}>
    COMMAND_EXPAND_LISTS
  )
endforeach()
