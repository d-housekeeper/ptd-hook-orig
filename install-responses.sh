#!/usr/bin/env bash
export MSYS_NO_PATHCONV=1 # required on msys
adb push ./out/Responses /storage/emulated/0/Android/data/com.square_enix.android_googleplay.PTD/files/
