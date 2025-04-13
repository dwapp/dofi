{
  stdenv,
  lib,
  nix-filter,
  fetchFromGitHub,
  cmake,
  pkg-config,
  wayland-scanner,
  wrapQtAppsHook,
  qtbase,
  qtdeclarative,
  qtwayland,
  layer-shell-qt,
}:

stdenv.mkDerivation rec {
  pname = "dofi";
  version = "0.0.1";

  src = nix-filter.filter {
    root = ./..;

    exclude = [
      ".git"
      "debian"
      "LICENSES"
      "README.md"
      (nix-filter.matchExt "nix")
    ];
  };

  nativeBuildInputs = [
    cmake
    pkg-config
    wayland-scanner
    wrapQtAppsHook
  ];

  buildInputs = [
    qtbase
    qtdeclarative
    qtwayland
    layer-shell-qt
  ];

  strictDeps = true;

  meta = {
    description = "Simple qml application launcher for wayland inspired by rofi";
    homepage = "https://github.com/dwapp/dofi";
    license = lib.licenses.gpl3Plus;
    platforms = lib.platforms.linux;
    maintainers = with lib.maintainers; [ rewine ];
  };
}
