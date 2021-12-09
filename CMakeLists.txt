cmake_minimum_required(VERSION 3.18)
project(ptd-hook)

option(FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." FALSE)
if(${FORCE_COLORED_OUTPUT})
  add_compile_options(
    $<$<CXX_COMPILER_ID:GNU>:-fdiagnostics-color=always>
    $<$<CXX_COMPILER_ID:Clang>:-fcolor-diagnostics>
  )
endif()

add_subdirectory(acd)
add_subdirectory(hook)
