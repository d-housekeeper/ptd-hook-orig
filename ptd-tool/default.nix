{ buildGoApplication
, fetchurl
, jq
, lib
, unzip
}:
buildGoApplication rec {
  pname = "ptd-tool";
  version = "19c9e555b92b4453fa7dbff16a67fe9e0e4e06f8";
  buildInputs = [ jq ];
  nativeBuildInputs = [ unzip ];
  src = fetchurl {
    url = "https://gitee.com/binaryeater/ptd-tool/repository/archive/${version}.zip";
    sha256 = "1x1pp7nikf8d9l5a1i3j9mg5rs6nf3xfcsaxi8in6vv01kfq5knr";
  };
  modules = ./gomod2nix.toml;
  postBuild = ''
    mkdir -p $out/bin/
    cp ./generate-md-assets.sh $out/bin/
    cp -R ./assets/ $out/bin/assets/
  '';
}
