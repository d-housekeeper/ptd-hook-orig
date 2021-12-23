{ buildGoApplication
, fetchurl
, jq
, lib
, unzip
}:
buildGoApplication rec {
  pname = "ptd-tool";
  version = "f3f2cf565710c66fc3911f8ecf734e947d01c976";
  buildInputs = [ jq ];
  nativeBuildInputs = [ unzip ];
  src = fetchurl {
    url = "https://gitee.com/binaryeater/ptd-tool/repository/archive/${version}.zip";
    sha256 = "1wzvk6kxf1dhhf94adpz6lb5381bl9fxfxdq2faygbr95h1fm8ay";
  };
  modules = ./gomod2nix.toml;
  postBuild = ''
    mkdir -p $out/bin/
    cp ./generate-md-assets.sh $out/bin/
    cp -R ./assets/ $out/bin/assets/
  '';
}
