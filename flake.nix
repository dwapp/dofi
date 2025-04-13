{
  description = "A basic flake to help develop dofi";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    nix-filter.url = "github:numtide/nix-filter";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
      nix-filter,
    }@input:
    flake-utils.lib.eachSystem [ "x86_64-linux" "aarch64-linux" "riscv64-linux" ] (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};

        dofi = pkgs.kdePackages.callPackage ./nix {
          nix-filter = nix-filter.lib;
        };
      in
      {
        packages.default = dofi;

        devShells.default = pkgs.mkShell {
          inputsFrom = [
            self.packages.${system}.default
          ];

          shellHook =
            let
              makeQtpluginPath = pkgs.lib.makeSearchPathOutput "out" pkgs.qt6.qtbase.qtPluginPrefix;
              makeQmlpluginPath = pkgs.lib.makeSearchPathOutput "out" pkgs.qt6.qtbase.qtQmlPrefix;
            in
            ''
              #export QT_LOGGING_RULES="*.debug=true;qt.*.debug=false"
              export QT_PLUGIN_PATH=${
                makeQtpluginPath (
                  with pkgs.kdePackages;
                  [
                    qtbase
                    qtdeclarative
                    qtwayland
                    layer-shell-qt
                  ]
                )
              }
              export QML2_IMPORT_PATH=${
                makeQmlpluginPath (
                  with pkgs.kdePackages;
                  [
                    qtdeclarative
                    layer-shell-qt
                  ]
                )
              }
              export QML_IMPORT_PATH=$QML2_IMPORT_PATH
            '';
        };
      }
    );
}
