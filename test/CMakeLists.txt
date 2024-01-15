list(APPEND tests
  # Core

  message

  # Components

  image/basic

  scroll-view/basic

  text/basic

  text-input/basic

  video/basic

  web-view/basic
  web-view/message

  window/basic
  window/destroy-on-close
  window/no-frame
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
    TIMEOUT 30000
  )
endforeach()
