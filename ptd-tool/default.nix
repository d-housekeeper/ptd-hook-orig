{ buildGoApplication
, fetchurl
, jq
, lib
, unzip }:
buildGoApplication rec {
  pname = "ptd-tool";
  version = "7517c87d68557040bfed34d094aa0d93f3750bc6";
  buildInputs = [ jq ];
  nativeBuildInputs = [ unzip ];
  src = fetchurl {
    url = "https://gitee.com/binaryeater/ptd-tool/repository/archive/${version}.zip";
    sha256 = "0m32530cgcq4irmdz0191ji7pjwcvyvry47vmkpj6blqc3nhxnib";
  };
  modules = ./gomod2nix.toml;
  postBuild = ''
    mkdir -p $out/bin/
    cp ./generate-md-assets.sh $out/bin/
    cp -R ./assets/ $out/bin/assets/
  '';
}
