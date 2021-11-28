#!/usr/bin/env bash
set -eu

rm -rf ./out/cpp
Il2CppInspector -i PTD.apk --select-outputs --cpp-out ./out/cpp

rm ./out/cpp/appdata/il2cpp-functions.h
cp ./out/cpp/appdata/*.h ./hook/appdata/

apktool d -f ./PTD.apk -o ./out/apktool
APKTOOL_OUTPUT_EXPECTED_HASH="$(cat apktool-output-hash.txt)"
APKTOOL_OUTPUT_HASH="$(nix hash-path ./out/apktool)"
if [ "$APKTOOL_OUTPUT_EXPECTED_HASH" != "$APKTOOL_OUTPUT_HASH" ]; then
  echo 'error: SHA256 hash did not match the expected value'
  exit 1
fi

rm -rf ./out/main
mkdir -p ./out/main
cp ./out/apktool/lib/armeabi-v7a/libmain.so ./out/main/
patchelf ./out/main/libmain.so --add-needed libhook.so
