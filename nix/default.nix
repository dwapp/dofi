{ stdenv
, lib
, nix-filter
, fetchFromGitHub
, cmake
, pkg-config
, wayland-scanner
, wrapQtAppsHook
, qtbase
, qtdeclarative
, qtwayland
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
  ];

  strictDeps = true;

  meta = with lib; {
    description = "A qml application launcher for wayland inspired by rofi";
    homepage = "https://github.com/dwapp/dofi";
    license = licenses.gpl3Plus;
    platforms = platforms.linux;
  };
}

