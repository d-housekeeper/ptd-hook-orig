{ buildGoApplication
, fetchurl
, jq
, lib
, unzip
}:
buildGoApplication rec {
  pname = "ptd-tool";
  version = "234c29c88260f5ac85c5f9d7310f8dc6ae7f88fc";
  buildInputs = [ jq ];
  nativeBuildInputs = [ unzip ];
  src = fetchurl {
    url = "https://gitee.com/binaryeater/ptd-tool/repository/archive/${version}.zip";
    sha256 = "1nfv9wqd1l41ji8h63iz9fd9f5sldp4kidpmjsqb5983r24z460a";
  };
  modules = ./gomod2nix.toml;
  postBuild = ''
    mkdir -p $out/bin/
    cp ./generate-md-assets.sh $out/bin/
    cp -R ./assets/ $out/bin/assets/
  '';
}
