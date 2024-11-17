{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = import nixpkgs {
            inherit system;
          };
        in
        rec {
          packages.pico-ssd1306 = pkgs.stdenv.mkDerivation {
            name = "pico-ssd1306";
            src = ./.;
            env = {
              PICO_SDK_PATH = "${pkgs.pico-sdk}/lib/pico-sdk";
            };
            nativeBuildInputs = with pkgs; [
              cmake
              gcc-arm-embedded
              python39
            ];
            cmakeFlags = [
              "-DCMAKE_C_COMPILER=${pkgs.gcc-arm-embedded}/bin/arm-none-eabi-gcc"
              "-DCMAKE_CXX_COMPILER=${pkgs.gcc-arm-embedded}/bin/arm-none-eabi-g++"
            ];
            installPhase = ''
              runHook preInstall
              mkdir -p $out/lib
              mkdir -p $out/include/pico-ssd1306
              cp libpico-ssd1306.a $out/lib/
              cp $src/include/* $out/include/pico-ssd1306/
              runHook postInstall
            '';
          };
          packages.default = packages.pico-ssd1306;
        }
      );
}
