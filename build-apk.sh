#!/usr/bin/env bash
set -eu
: "$KEYSTORE_FILE"
cp -R ./smali/ ./out/apktool/
cp AndroidManifest.xml ./out/apktool/
cp out/cmake/hook/libhook.so out/cmake/acd/lib__57d5__.so ./out/apktool/lib/armeabi-v7a/

pushd ./out/apktool/
apktool b -f -o ../PTD_tmp.apk
popd

jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore "$KEYSTORE_FILE" ./out/PTD_tmp.apk alias_name
rm -f ./out/PTD_modded.apk
zipalign -v 4 ./out/PTD_tmp.apk  ./out/PTD_modded.apk
rm ./out/PTD_tmp.apk
