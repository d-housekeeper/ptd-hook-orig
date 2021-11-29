#!/usr/bin/env bash
set -eu

rm -rf ./out/cpp
Il2CppInspector -i PTD.apk --select-outputs --cpp-out ./out/cpp

rm ./out/cpp/appdata/il2cpp-functions.h
cp ./out/cpp/appdata/*.h ./hook/appdata/

apktool d -f ./PTD.apk -o ./out/apktool

rm -rf ./out/main
mkdir -p ./out/main
cp ./out/apktool/lib/armeabi-v7a/libmain.so ./out/main/
patchelf ./out/main/libmain.so --add-needed libhook.so
