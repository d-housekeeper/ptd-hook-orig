#!/usr/bin/env bash
set -eu
export MSYS_NO_PATHCONV=1 # required on msys
adb shell am force-stop com.square_enix.android_googleplay.PTD
adb shell am start -n com.square_enix.android_googleplay.PTD/com.unity3d.player.UnityPlayerActivity
