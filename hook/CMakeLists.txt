cmake_minimum_required(VERSION 3.18.1)
project(hook)

set(FRIDA_GUM_DEVKIT_DIR "frida-gum-devkit")
set(CMAKE_CXX_STANDARD 20)

add_library(hook
  SHARED
  dlopen-hook.cpp
  api-mod.cpp
  game-initializer-mod.cpp
  local-data-mod.cpp
  md-mod.cpp
  ui-mod.cpp
  framework/helpers.cpp
  framework/il2cpp-init.cpp
  response-loader.cpp
  responses/equipment-avatar-response.cpp
  responses/login-response.cpp
  responses/response-utils.cpp
  responses/set-favorite-character-response.cpp
  responses/set-idol-class-response.cpp
  responses/set-team-response.cpp
  responses/start-lesson-response.cpp
  responses/start-quest-response.cpp
  responses/stored-response.cpp
  android-storage-path.cpp
  time-utils.cpp
  jni-utils.cpp
  config.cpp
  main.cpp
  )
include_directories(frida-gum-devkit
  date
  appdata
  framework
  ./
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
