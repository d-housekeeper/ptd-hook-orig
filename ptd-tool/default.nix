{ buildGoApplication
, fetchurl
, jq
, lib
, unzip
}:
buildGoApplication rec {
  pname = "ptd-tool";
  version = "8598cd75c3df84df973675402e5b7cc217552cdc";
  buildInputs = [ jq ];
  nativeBuildInputs = [ unzip ];
  src = fetchurl {
    url = "https://gitee.com/binaryeater/ptd-tool/repository/archive/${version}.zip";
    sha256 = "1nn48cidi8s6fqqa67vz1dc8ghxba9kra4ia93q3jw9jmjz9q6ws";
  };
  modules = ./gomod2nix.toml;
  postBuild = ''
    mkdir -p $out/bin/
    cp ./generate-md-assets.sh $out/bin/
    cp -R ./assets/ $out/bin/assets/
  '';
}
