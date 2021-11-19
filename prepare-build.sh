#!/usr/bin/env bash
set -eu
HASH_STATUS=0
echo "$(cat PTD.apk.sha256) PTD.apk" | sha256sum --check --status || HASH_STATUS=$?
if [ "$HASH_STATUS" = 1 ]; then
  echo 'error: SHA256 hash did not match the expected value'
  exit 1
fi

rm -rf ./out/cpp
Il2CppInspector -i PTD.apk --select-outputs --cpp-out ./out/cpp

rm ./out/cpp/appdata/il2cpp-functions.h
cp ./out/cpp/appdata/*.h ./hook/appdata/

rm -rf ./out/main
mkdir -p ./out/main
unzip -j PTD.apk lib/armeabi-v7a/libmain.so -d ./out/main/
patchelf ./out/main/libmain.so --add-needed libhook.so
