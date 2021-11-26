{ buildGoApplication
, fetchurl
, jq
, lib
, unzip }:
buildGoApplication rec {
  pname = "ptd-tool";
  version = "29098e8a8f22ea70c0b9f7d729daac351b3973e6";
  buildInputs = [ jq ];
  nativeBuildInputs = [ unzip ];
  src = fetchurl {
    url = "https://gitee.com/binaryeater/ptd-tool/repository/archive/${version}.zip";
    sha256 = "15cw36214zg510y9m8jmcd9d4g1w47q1khdgl46qbz9sj2il66lf";
  };
  modules = ./gomod2nix.toml;
  postBuild = ''
    mkdir -p $out/bin/
    cp ./generate-md-assets.sh $out/bin/
    cp -R ./assets/ $out/bin/assets/
  '';
}
