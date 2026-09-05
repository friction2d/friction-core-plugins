# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.12)
project(FreeDesktopNotifyPlugin)

friction_add_plugin(${PROJECT_NAME}
    freedesktop-notify.cpp
    freedesktop-notify.h
)

if(UNIX AND NOT APPLE)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS DBus REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::DBus)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_DBUS)
endif()
