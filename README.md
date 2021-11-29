# ptd-hook

## Introduction

A PTD mod which let you play some part of the games after service shutdown on 2021/10/29...
Use at your own risk, read instructions carefully, and make backup before proceeding.

With this mod, you can at least

* interact with dolls on home screen and in their room
* read stories
* set dolls' classes/clothes
* watching dolls' skill animation

Changes to user data is lost after restart, because the mod does not do anything for storing changes. What it does is returning HTTP response stored in internal storage.

## What does this mod do internally?

* Installs hooks to disable all requests with `UnityWebRequest` wrapper class used by the game, and replaces responses with ones stored in internal storage.
* The mod supports 2 installation methods: install with modded apk, or direct install with root permissions.
* Replaces connect system call with AF_INET or AF_INET6 to block all web requests from the app. This is technically not required when installing mod with apk modding method, as network permission on AndroidManifest.xml is removed after rebuilding apk. For installation with root permission, this is still required.
* Disables anti cheat library embedded in the apk.

## Prerequisites

* You need to have an Android device (or an emulator device) with PTD apk, assets and local save data.
  * I recommend setting up a fresh environment on emulators like BlueStacks and restore backup there to make sure that your backup contains all data the app needs. You can restore save data from the backup in case something go wrong.
  * The apk must be the latest version before service shutdown (5.1.10). Any version newer or older will not work.
  * If you are using an emulator, use apk modding method even if you have root permissions. I only confirmed root installation method to work on real Android devices. Emulators does not seem to like libmain.so modded with patchelf. At least on BlueStacks 5, the app always crashes at launch. Maybe issues with libhoudini, but I'm not sure.
  * You need to have a copy of downloaded assets on development machine to generate login response. It must at least contain directory named `md`.

Build environment setup is automated with nix.
You need a linux machine (either real machine or virtual machine) with nix installed: https://nixos.org/download.html

Before running build scripts, get PTD's apk from your backup, and rename it to `PTD.apk`, and place it in the root directory of this repo. Then start a subshell with `nix-shell`.

```
nix-shell
```

On non-linux machines you could also use docker. It can also be used on linux, but all files created by scripts owned by root.

```
docker run --rm -it -v ptd-hook-nix:/nix -v $PWD:/work -w /work nixos/nix nix-shell
```

adb command will not be installed automatically. To run scripts that need adb to work, run them on host machine.
(There are ways to run adb from virtual machine, though I do not go into detail here)
## Building

1. Run `./prepare-build.sh`. You only need to run once.

```
./prepare-build.sh
```

The script does following:

* Creates C++ header with Il2CppInspector for shared library (.so file) injection. As I only put small subset of generated headers here to avoid copying copyrighted materials as much as possible, you need to generate most of them by yourself.
* extracts libmain.so from apk, and runs patchelf to make it load injection library which we will build in next step. Required for installation with root permissions.
* decompile the apk with apktool. Required for installation with modded apk.

If you want to be sure that you are using right version of the apk as the base, run following right after running:

```
./check-input-apk.sh
```

This might not work correctly if you clone this repo in windows filesystem. Run git clone on linux filesystem to get correct results.
This will also fail after running `./build-apk.sh` at least once, as the script changes contents on `./out/apktool/`


2. run `./build.sh`

```
./build.sh
```

Runs cmake and make to build libhook.so and replacement lib__57d5__.so to disable anti cheat.

## Installing with root permissions

After building, run `./install-with-su.sh` on host machine to install the mod to app's library directory.

```
./install-with-su.sh
```

## Installing with modded APK

You need to uninstall original app first if you already have one, otherwise modded one won't install because apk's signature is different. All app data will be lost after uninstalling the app, including one on `/sdcard/Android/data/[app package name]`. As I said earlier, I would recommend setting up the mod on a different device first to make sure that your backup is okay.

If you don't have one, create a keystore file for resigning the apk.

```
keytool -genkey -v -keystore my-release-key.keystore -alias alias_name -keyalg RSA -keysize 2048 -validity 10000
```

Run this command to build the apk.
Replace `~/path/to/release-key.keystore` with actual path of key store.

```
KEYSTORE_FILE=~/path/to/release-key.keystore ./build-apk.sh
```

You can then install the apk with adb.

```
adb install -r ./out/PTD_modded.apk
```

## Sending server response files to Android device

The mod reads responses from files stored in internal storage. It can only read already decrypted, uncompressed response. On the other hand, the response should be minified and should not contain line breaks. You can use [ptd-tool](https://gitee.com/binaryeater/ptd-tool) if you have captured response before shutdown.

You can then send responses to Android device like this.

```
adb push Login.json /storage/emulated/0/Android/data/com.square_enix.android_googleplay.PTD/files/Responses/
```

If the hook fails to find json file on internal storage, it prints logs to logcat. See logs with `adb logcat -s PTDHook` to see which API response is required.

```
Failed to load response file from /storage/emulated/0/Android/data/com.square_enix.android_googleplay.PTD/files/Responses/EquipmentAvatar.json
```

`GetNativeToken` is automatically replaced with one embedded in the injection library so you don't need to prepare one by yourself.

## Generating login responses

nix-shell also setup tools for generating login responses, which will allow you to run the app without responses captured by yourself.
Running `./prepare-response-generator.sh` sets up decoded MD files and configuration file needed for running the tool.
Replace `/path/to/md/` with actual path to MD directory on your machine.

```
MD_SRC_DIR=/path/to/md/ ./prepare-response-generator.sh
```

Then run `./generate-responses.sh` to generate login response in temporary directory, and copies all response json files stored in `responses-input` directory and minify them.

```
./generate-responses.sh
```

To send generated responses to Android device, use `./install-responses.sh`.

```
./install-responses.sh
```

## Other helper scripts

You can launch the app using adb with `./launch-activity.sh`.

```
./launch-activity.sh
```
