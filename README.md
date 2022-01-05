# ptd-hook

## Introduction

A PTD mod which let you play some part of the games after service shutdown on 2021/10/29...
Use at your own risk, read instructions carefully, and make backup before proceeding.

With this mod, you can

* interact with dolls on home screen and in their room
* read stories
* set characters' classes/clothes
* watching characters' skill animation
* play quests (battles)

Only following changes to user data persists after restart. Everything else will get lost after restarting the app.

* Favorite character (お気に入り)
* Costumes currently characters are wearing  (着せ替え)
* Teams (パーティ編成)
* Interrupted quest data

The mod also adds additional features that didn't exist even in original version of the app.

* Setting a different time than current time. Useful for listening to interaction voices that are only available for limited time.
  * Many of past event stories and quests don't work correctly. Might still be useful for viewing illusts of past events. If you just want to read stories of past events, try finding one in story reminiscence (ストーリー回想).
  * By default current time and time zone of the device is used.
* Forcing portrait mode in home scene, my room scene (女子寮), and photo mode scene (撮影モード). Useful for seeing costume design for lower part of body or for zooming characters' face without switching to view mode.
  * Some of UI elements can be hidden for those scenes as well.

## PTDHook Settings activity

The mod creates an ongoing notification, which is accessible only when the app is in foreground. Tapping the notification opens mod settings in another Android activity. Additional mod features we described above can be toggled/tweaked from this activity.

If you don't want the notification to show up, just disable the notification from Android settings.
Alternatively you can add shortcut to home screen from this activity, to easily access settings without tapping notification. (Only works on Android 8.0+)

## What does this mod do internally?

* Installs hooks to disable all requests with `UnityWebRequest` wrapper class used by the game, and replaces responses with ones stored in internal storage. Server time and some other fields are added to the response by the mod automatically.
  * For some API endpoints, the hook generates response content dynamically and patches Login response to persist changes.
* Removes network permission from AndroidManifest.xml to prevent any attempts of network connection.
* Disables anti cheat library embedded in the apk by replacing it with dummy one. This only works with this specific version of PTD, as the antiCheatValues changed between releases of the app. It will probably not work on other apps either. I will not write how I got those values, because that might make disabling cheat detection on other games easier. (Other games might be using more sophisticated cheat detection techniques and can't be disabled in the same way, I just don't know.)
* Overrides some of local data fields to trick the app into believing that you already have player data locally.
* Prevents `sign in to Google` activity from showing up when you launch the app for the first time.
* Prevents movies from being downloaded. Movies will get deleted after playing, so it won't exist on your disk even if you downloaded all assets before service shutdown.
* Modifies Shinjuku Naraku event data to prevent it from expiring. (Expired Shinjuku Naraku event causes the app to crash)
* Skips initialization of some event details to avoid crashes after changing to event details scene.
* If enabled, changes camera position and/or hides some of UI elements when some of scenes are initialized. Config file is loaded every time when those scenes are initialized until you disable loading of UI mod and restart the app.
* Creates modded apk to install those modified/added files. Re-installing the apk with different signing key also prevents updates from showing up on Google Play.

## Prerequisites

* You need to have an Android device (or an emulator device) with PTD apk, assets directory (`md`, `prim`) and some of files in `SaveData` directory.
  * `pa.ds` and `ver_0.ds` in `SaveData` directory keep truck of downloaded assets, and are required along with `md` and `prim` directory.
  * I recommend setting up a fresh environment on emulators like BlueStacks and restore backup there to make sure that your backup contains all data the app needs. You can restore save data from the backup, or delete all files in SaveData and restore `pa.ds` and `ver_0.ds` again to restart from fresh state.
  * The apk must be the latest version before service shutdown (5.1.10). Any version newer or older will not work.
  * You need to have a copy of `md` directory on development machine to generate login response.
  * Keystore file for re-signing modded apk. Create new one with `keytool` if you don't already have one.
  * If you have previously signed into the game, revoke app permission on Google account security settings, just in case.

Build environment setup is automated with nix package manager.
You need a linux machine (either real machine or virtual machine) with nix installed: https://nixos.org/download.html

If you are running this on NixOS, you also need to install nix-ld to run aapt2 from gradle build: https://github.com/Mic92/nix-ld

Before running build scripts, get PTD's apk from your backup, and rename it to `PTD.apk`, and place it in the root directory of this repo. Then start a subshell with `nix-shell`.

```
nix-shell
```

adb command will not be installed automatically. To run scripts that need adb to work, run them on host machine.
(There are ways to run adb from virtual machine, though I do not go into detail here)

If you don't have one, create a keystore file for re-signing the apk.

```
keytool -genkey -v -keystore release-key.keystore -alias alias_name -keyalg RSA -keysize 2048 -validity 10000
```

## Building

1. Run `./prepare-build.sh`. You only need to run once.

```
./prepare-build.sh
```

The script does following:

* Creates C++ header with Il2CppInspector for shared library (.so file) injection. As I only put small subset of generated headers here to avoid copying copyrighted materials as much as possible, you need to generate most of them by yourself.
* decompile the apk with apktool. Required for installation with modded apk.

If you want to be sure that you are using right version of the apk as the base, run following right after running:

```
./check-input-apk.sh
```

This might not work correctly if you clone this repo in windows filesystem. Run git clone on linux filesystem to get correct results.
This will also fail after running `./build.sh` at least once, as the script changes contents on `./out/apktool/`

2. run `./build.sh`

Run this command to build C++ libraries and modded apk.
Replace `~/path/to/release-key.keystore` with actual path of key store.

```
KEYSTORE_FILE=~/path/to/release-key.keystore ./build.sh
```

## Installing with modded APK

You need to uninstall original app first if you already have one, otherwise modded one won't install because apk's signature is different. All app data will be lost after uninstalling the app, including one on `/sdcard/Android/data/[app package name]`. As I said earlier, I would recommend setting up the mod on a different device first to make sure that your backup is okay.
(Or, temporarily rename sdcard data directory to something different to prevent it from being removed)

You can then install the apk with adb.

```
adb install -r ./out/PTD_modded.apk
```

## Sending server response files to Android device

The mod reads responses from files stored in internal storage. It can only read already decrypted, uncompressed response. On the other hand, the response should be minified and should not contain line breaks. You can use [ptd-tool](https://gitee.com/binaryeater/ptd-tool) if you have captured response before shutdown.
Send decoded json to `/sdcard/Android/data/com.square_enix.android_googleplay.PTD/files/Responses/` for the mod to pick up. I recommend using `adb push` for doing so.

If the hook fails to find json file on internal storage, it prints filename to logcat. See logs with `adb logcat -s PTDHook` to see which API response is required.

```
Failed to load response file from /storage/emulated/0/Android/data/com.square_enix.android_googleplay.PTD/files/Responses/EquipmentAvatar.json
```

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

## Licensing

See `LICENSE` file.

Basically the license allows everything, but please don't do nonsense. Use your common sense.
Forking and improving this mod or using non-PTD specific part as a base for another IL2CPP based game mod is totally fine.

frida-gum is licensed under wxWindows Library Licence. https://github.com/frida/frida-gum/blob/main/COPYING
For other header only libraries, see the beginning of file for the license.
