{ buildGoApplication
, fetchurl
, jq
, lib
, unzip
}:
buildGoApplication rec {
  pname = "ptd-tool";
  version = "8fbf613b1f9d3c76fcce052daf3c4f00ddd585a4";
  buildInputs = [ jq ];
  nativeBuildInputs = [ unzip ];
  src = fetchurl {
    url = "https://gitee.com/binaryeater/ptd-tool/repository/archive/${version}.zip";
    sha256 = "1dfsslw2ngbxnn5kf1bwi01d91gl3b06jqibj01i6sban794sjdi";
  };
  modules = ./gomod2nix.toml;
  postBuild = ''
    mkdir -p $out/bin/
    cp ./generate-md-assets.sh $out/bin/
    cp -R ./assets/ $out/bin/assets/
  '';
}
