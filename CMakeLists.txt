# SPDX-License-Identifier: GPL-3.0-only

add_custom_target(all_friction_plugins)

find_package(QT NAMES Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} 5.15.13 COMPONENTS Core Xml Qml Gui Widgets REQUIRED)

function(friction_add_plugin target_name)
    add_library(${target_name} MODULE ${ARGN} plugin.json)
    set_target_properties(${target_name} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        AUTOMOC ON
    )
    target_include_directories(${target_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/src/core
        ${CMAKE_SOURCE_DIR}/src/skia
    )
    target_link_libraries(${target_name} PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Xml
        Qt${QT_VERSION_MAJOR}::Qml
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        frictioncore
    )
    if(APPLE)
        set_target_properties(${target_name} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/app/friction.app/Contents/MacOS/plugins
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/app/friction.app/Contents/MacOS/plugins
        )
    else()
        set_target_properties(${target_name} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/app/plugins
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/app/plugins
        )
    endif()
    add_dependencies(all_friction_plugins ${target_name})
endfunction()

option(BUILD_PLG_HELLOWORLD "Build Hello World Plugin" OFF)
if(BUILD_PLG_HELLOWORLD)
    add_subdirectory(helloworld)
endif()

option(BUILD_PLG_IMPORTTXT "Build Import TXT Plugin" ON)
if(BUILD_PLG_IMPORTTXT)
    add_subdirectory(importtxt)
endif()

if(UNIX AND NOT APPLE)
    option(BUILD_PLG_LAUNCHERAPI "Build LauncherAPI Plugin" ON)
    if(BUILD_PLG_LAUNCHERAPI)
        add_subdirectory(launcherapi)
    endif()
    option(BUILD_PLG_FREEDESKTOP_POWER "Build Linux Power Plugin" ON)
    if(BUILD_PLG_FREEDESKTOP_POWER)
        add_subdirectory(freedesktop-power)
    endif()
endif()
