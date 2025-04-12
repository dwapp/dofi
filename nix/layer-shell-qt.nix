{ stdenv
, lib
, fetchFromGitHub
, cmake
, extra-cmake-modules
, pkg-config
, wayland-scanner
, wrapQtAppsHook
, qtbase
, qtdeclarative
, qtwayland
, wayland
, wayland-protocols
}:

stdenv.mkDerivation rec {
  pname = "layer-shell-qt";
  version = "5.81.80";

  src = fetchFromGitHub {
    owner = "KDE";
    repo = pname;
    rev = "25bc38dac1953019e97948b5eddd081bef3d16a3";
    hash = "sha256-wehWa1/mfFWrtLVDEk1ePFwlorhdfr+1Q58frESDd+4=";
  };

  nativeBuildInputs = [
    cmake
    extra-cmake-modules
    pkg-config
    wayland-scanner
    wrapQtAppsHook
  ];

  buildInputs = [
    qtbase
    qtdeclarative
    qtwayland
    wayland
    wayland-protocols
  ];

  meta = with lib; {
    description = "This component is meant for applications to be able to easily use clients based on wlr-layer-shell";
    homepage = "https://github.com/KDE/layer-shell-qt";
    license = licenses.gpl3Plus;
    platforms = platforms.linux;
  };
}

