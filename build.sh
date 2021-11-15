#!/usr/bin/env sh
cmake . -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake" \
  -B./out/cmake \
  -DANDROID_PLATFORM=21 \
  -DANDROID_ABI=armeabi-v7a \
  -DCMAKE_BUILD_TYPE=Release
cd ./out/cmake
make
