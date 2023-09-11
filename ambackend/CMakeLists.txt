set(DEMO_SOURCE
    entry.cpp
    application.h
    application.cpp
    applicationmanager.h
    applicationmanager.cpp
)

set_source_files_properties(
   "${CMAKE_CURRENT_SOURCE_DIR}/org.desktopspec.ApplicationManager1.xml" PROPERTIES
   INCLUDE "types.h"
)

set_source_files_properties(
    "${CMAKE_CURRENT_SOURCE_DIR}/org.desktopspec.ApplicationManager1.Application.xml" PROPERTIES
   INCLUDE "types.h"
)

qt_add_dbus_interface(AM_INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/org.desktopspec.ApplicationManager1.xml"
    "ApplicationManager"
)

qt_add_dbus_interface(AM_INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/org.desktopspec.ApplicationManager1.Application.xml"
    "Application"
)


add_executable(treeland-session-entry ${DEMO_SOURCE} ${AM_INTERFACE})
target_link_libraries(treeland-session-entry
    PUBLIC
    Qt6::Core
    Qt6::DBus
    Qt6::Network
)
