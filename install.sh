#!/usr/bin/env sh
set -eu
export MSYS_NO_PATHCONV=1 # required on msys
adb push apply-mod.sh out/cmake/hook/libhook.so out/main/libmain.so out/cmake/acd/lib__57d5__.so /data/local/tmp/
adb shell chmod +x /data/local/tmp/apply-mod.sh
adb shell su -c /data/local/tmp/apply-mod.sh
