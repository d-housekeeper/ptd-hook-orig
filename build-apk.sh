#!/usr/bin/env bash
set -eu
apktool d -f ./PTD.apk -o ./out/apktool
cp -R ./smali/ ./out/apktool/
cp AndroidManifest.xml ./out/apktool/
cp out/cmake/hook/libhook.so out/cmake/acd/lib__57d5__.so ./out/apktool/lib/armeabi-v7a/

pushd ./out/apktool/
apktool b -f -o ../PTD_modded.apk
popd

jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore release-key.keystore ./out/PTD_modded.apk alias_name
rm ./out/PTD_modded_aligned.apk
zipalign -v 4 ./out/PTD_modded.apk  ./out/PTD_modded_aligned.apk
rm ./out/PTD_modded.apk
