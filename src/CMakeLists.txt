find_package(Qt6 6.4 REQUIRED COMPONENTS Core Quick DBus Network)
find_package(LayerShellQt REQUIRED)

qt_standard_project_setup()

if(QT_KNOWN_POLICY_QTP0001) # this policy was introduced in Qt 6.5
    qt_policy(SET QTP0001 NEW)
    # the RESOURCE_PREFIX argument for qt_add_qml_module() defaults to ":/qt/qml/"
endif()

add_subdirectory(ambackend)

qt_add_executable(dofi
    main.cpp
)

qt_add_qml_module(dofi
    URI Dofi
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES DLauncher.qml
    SOURCES launcherlistmodel.h launcherlistmodel.cpp
    SOURCES modelhelperimpl.h modelhelperimpl.cpp
    SOURCES dmenuimpl.h dmenuimpl.cpp
    SOURCES amimpl.h amimpl.cpp
)

set_target_properties(dofi PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appuntitled1
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(dofi
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ambackend
)

target_link_libraries(dofi
    PRIVATE
    $<TARGET_OBJECTS:application-manager-entry>
    Qt6::Quick
    Qt6::Core
    Qt6::DBus
    Qt6::Network
    LayerShellQt::Interface
)

target_compile_definitions(dofi
    PRIVATE
    LIBEXEC_PATH="${CMAKE_INSTALL_FULL_LIBEXECDIR}"
)

install(PROGRAMS dmenu_path DESTINATION ${CMAKE_INSTALL_LIBEXECDIR})

install(TARGETS dofi
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
