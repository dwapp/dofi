cmake_minimum_required(VERSION 3.16)

project(dLauncher VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Core Quick DBus Network)

qt_standard_project_setup()

if(QT_KNOWN_POLICY_QTP0001) # this policy was introduced in Qt 6.5
    qt_policy(SET QTP0001 NEW)
    # the RESOURCE_PREFIX argument for qt_add_qml_module() defaults to ":/qt/qml/"
endif()

add_subdirectory(ambackend)

qt_add_executable(dLauncher
    main.cpp
)

qt_add_qml_module(dLauncher
    URI DLauncher
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES DLauncher.qml
    SOURCES launcherlistmodel.h launcherlistmodel.cpp
    SOURCES
    SOURCES amlistmodel.h amlistmodel.cpp
)

set_target_properties(dLauncher PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appuntitled1
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(dLauncher
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ambackend
)

target_link_libraries(dLauncher
    PRIVATE
    $<TARGET_OBJECTS:treeland-session-entry>
    Qt6::Quick
    Qt6::Core
    Qt6::DBus
    Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS dLauncher
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
