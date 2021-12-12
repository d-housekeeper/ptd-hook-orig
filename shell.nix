let
  sources = import ./nix/sources.nix;
  pkgs = import sources.nixpkgs {
    config = {
      android_sdk.accept_license = true;
    };
    overlays = [
      (self: super: {
        buildGoApplication = super.callPackage "${sources.gomod2nix}/builder" { };
        gomod2nix = super.callPackage sources.gomod2nix { };
      })
    ];
  };
  il2cppinspector = pkgs.callPackage ./il2cppinspector/default.nix { };
  baksmali = pkgs.callPackage ./baksmali/default.nix { };
  ptd-tool = pkgs.callPackage ./ptd-tool/default.nix { };
  androidComposition = pkgs.androidenv.composeAndroidPackages {
    includeNDK = true;
    cmakeVersions = [ "3.18.1" ];
    platformVersions = [ "31" ];
  };
  build-tools = pkgs.lib.head androidComposition.build-tools;
  cmake = pkgs.lib.head androidComposition.cmake;
  gradlePackages = pkgs.callPackage (import "${sources.nixpkgs}/pkgs/development/tools/build-managers/gradle/default.nix") { };
in
pkgs.mkShell rec {
  ANDROID_SDK_ROOT = "${androidComposition.androidsdk}/libexec/android-sdk";
  ANDROID_NDK_ROOT = "${ANDROID_SDK_ROOT}/ndk-bundle";

  buildInputs = [
    il2cppinspector
    ptd-tool
    gradlePackages.gradle_7_3
    baksmali
  ] ++ (with pkgs; [
    jq
    hashdeep
    apktool
    jdk
  ]);

  shellHook = ''
    export PATH="$ANDROID_SDK_ROOT/cmake/${cmake.version}/bin:$ANDROID_SDK_ROOT/build-tools/${build-tools.version}/:$PATH"
    export PTD_TOOL_DIR="${ptd-tool}"
  '';
}
