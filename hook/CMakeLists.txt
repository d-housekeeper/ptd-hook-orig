cmake_minimum_required(VERSION 3.18.1)
project(hook)

set(FRIDA_GUM_DEVKIT_DIR "frida-gum-devkit")

add_library(hook
  SHARED
  dlopen-hook.cpp
  api-mod.cpp
  framework/helpers.cpp
  framework/il2cpp-init.cpp
  response-loader.cpp
  disable-connect-hook.cpp
  local-data-mod.cpp
  main.cpp)
include_directories(frida-gum-devkit
  appdata
  framework
  )
target_precompile_headers(hook PRIVATE framework/pch-il2cpp.h)
target_link_libraries(hook
  log
  ${CMAKE_CURRENT_SOURCE_DIR}/frida-gum-devkit/libfrida-gum.a)
add_custom_command(TARGET hook POST_BUILD
  COMMAND "${ANDROID_TOOLCHAIN_PREFIX}strip" --strip-unneeded
  "${CMAKE_CURRENT_BINARY_DIR}/libhook.so"
  COMMENT "Strip debug symbols done on final binary.")
set_target_properties(hook PROPERTIES CXX_VISIBILITY_PRESET hidden)
