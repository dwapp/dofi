cmake_minimum_required(VERSION 3.16)

project(dLauncher VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Core Quick DBus Network)

qt_standard_project_setup()

add_subdirectory(ambackend)

qt_add_executable(dLauncher
    main.cpp
)

qt_add_qml_module(dLauncher
    URI DLauncher
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES DLauncher.qml
    SOURCES dhelperbase.h dhelperbase.cpp
    SOURCES launcherlistmodel.h launcherlistmodel.cpp
    SOURCES laitemdata.h laitemdata.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(dLauncher PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appuntitled1
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(dLauncher
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS dLauncher
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
