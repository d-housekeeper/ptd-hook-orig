{ lib, stdenv, fetchurl, makeWrapper, jre }:

stdenv.mkDerivation rec {
  pname = "baksmali";
  version = "2.5.2";

  src = fetchurl {
    url = "https://bitbucket.org/JesusFreke/smali/downloads/baksmali-${version}.jar";
    sha256 = "1rfjp8zwagcpffshmvbfvwnz9bsxwxggkdqylg2jxy74ri4644fk";
  };

  dontUnpack = true;
  nativeBuildInputs = [ makeWrapper ];
  sourceRoot = ".";

  installPhase = ''
    install -D ${src} "$out/libexec/baksmali/baksmali.jar"
    mkdir -p "$out/bin"
    makeWrapper "${jre}/bin/java" "$out/bin/baksmali" \
        --add-flags "-jar $out/libexec/baksmali/baksmali.jar"
  '';
}
