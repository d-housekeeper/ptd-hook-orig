let
  sources = import ./nix/sources.nix;
  pkgs = import sources.nixpkgs { };
  il2cppinspector = pkgs.callPackage ./il2cppinspector/default.nix { };
in
il2cppinspector
