# ptd-hook

## Introduction

A PTD mod which let you play some part of the games after service shutdown on 2021/10/29... if you played the game on a rooted Android device, and captured server responses before shutdown. Use at your own risk.

With this mod, you can at least

* interact with dolls on home screen and in their room
* read stories
* set dolls' classes/clothes
* watching dolls' skill animation

Changes to user data is lost after restart. Most of user info is stored in login response, and currently the mod just returns fixed response.

## What does this mod do internally?

* Installs hooks to disable all requests with `UnityWebRequest` wrapper class used by the game, and replaces responses with ones stored in internal storage.
* Replaces connect system call with AF_INET or AF_INET6 to block all web requests from the app.
* Disables anti cheat library embedded in the apk.

## Prerequisites

* You need to have a rooted Android device with PTD apk, assets and local save data. Rooted device is required for applying the mod.
  * The apk must be latest version before service shutdown (5.1.10). Any version newer or older will not work.
  * If your local save data is on non-rooted device, there is no way to retrieve it. Even if your device supports bootloader unlocking (needed for rooting), you need to wipe user data to do that.
  * On an emulator, or on very old devices with unpatched vulnerability that allows rooting, it might be possible to root without losing data.
* Responses captured before shutdown are required.
  * As the game doesn't store most of player information locally and fetches them from server, Login response is necessary to work. If you don't have one, unfortunately you can't use this mod. It's hard to build one from scratch, I don't have time and energy for that. I don't I won't to paste full login response of my account here either, as that might reveal the account I used in the game.

To build, you need linux machine (either real machine or virtual machine) with nix installed: https://nixos.org/download.html

Before running build scripts, get PTD's apk from your backup, and rename it to `PTD.apk`, and place it in the root directory of this repo. Then create subshell with `nix-shell`.

On non-linux machines you could also use docker. It can also be used on linux, but all files created by scripts owned by root.

```
docker run --rm -it -v ptd-hook-nix:/nix -v $PWD:/work -w /work nixos/nix nix-shell
```

## Building

1. Run `./prepare-build.sh`. You only need to run once.

The script does following:

* Creates C++ header with Il2CppInspector for shared library (.so file) injection. As I only put small subset of generated headers here to avoid copying copyrighted materials as much as possible, you need to generate most of them by yourself.
* extracts libmain.so from apk, and runs patchelf to make it load injection library which we will build in next step.

2. run `./build.sh`

Runs cmake and make to build libhook.so and replacement lib__57d5__.so to disable anti cheat.

## Installation

After building, run `./install.sh` on host machine to install the mod to app's library directory.

Then send json files you want the hook library to use as replacement server responses. The mod can only read already decrypted, uncompressed response. You can use [ptd-tool](https://gitee.com/binaryeater/ptd-tool) if you have captured response before shutdown.

```
adb push Login.json /storage/emulated/0/Android/data/com.square_enix.android_googleplay.PTD/files/Responses
```

If the hook fails to find json file on internal storage, it prints logs to logcat. See logs with `adb logcat -s PTDHook` to see which API response is required.

```
Failed to load response file from /storage/emulated/0/Android/data/com.square_enix.android_googleplay.PTD/files/EquipmentAvatar.json
```

`GetNativeToken` is automatically replaced with one embedded in the injection library so you don't need to prepare one by yourself.
