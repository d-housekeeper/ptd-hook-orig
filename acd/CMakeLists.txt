cmake_minimum_required(VERSION 3.18.1)
project(__57d5__)

add_library(__57d5__
    SHARED
    main.cpp)
add_custom_command(TARGET __57d5__ POST_BUILD
  COMMAND "${ANDROID_TOOLCHAIN_PREFIX}strip" --strip-unneeded
  "${CMAKE_CURRENT_BINARY_DIR}/lib__57d5__.so"
  COMMENT "Strip debug symbols done on final binary.")
set_target_properties(__57d5__ PROPERTIES CXX_VISIBILITY_PRESET hidden)
