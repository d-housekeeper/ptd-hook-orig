{ lib
, fetchFromGitHub
, fetchurl
, buildDotnetModule
, dotnet-sdk_3
, dotnetCorePackages
, unzip
}:

buildDotnetModule rec {
  pname = "il2cppinspector";
  version = "2021.4";

  srcs = [
    (fetchFromGitHub {
      owner = "djkaty";
      repo = "Il2CppInspector";
      rev = "d2a30c01cd2fdc0497c7ad4b6a9b5f47bb7ebd2a";
      fetchSubmodules = true;
      name = pname;
      sha256 = "1b2hxb8808fa24771nzwyvr4sm9d91r7hs8yzvk2nrhsf8jbr7bb";
    })
    (fetchurl {
      url = "https://github.com/djkaty/Il2CppInspectorPlugins/releases/download/2021.01.31/plugins.zip";
      name = "plugins.zip";
      sha256 = "1g7lvjd7sh1sf65h7jvlxrk60mpj0r27xz2sxgr93s1grcgzkyc8";
    })
  ];

  patches = [
    ./nix-build-fix.patch
  ];

  nativeBuildInputs = [ unzip ];
  sourceRoot = "il2cppinspector";

  projectFile = "Il2CppInspector.sln";
  nugetDeps = ./deps.nix;
  dotnet-sdk = dotnet-sdk_3;
  dotnet-runtime = dotnetCorePackages.runtime_3_1;

  postInstall = ''
    cp -R ../plugins/ $out/lib/il2cppinspector/plugins/
  '';
}
