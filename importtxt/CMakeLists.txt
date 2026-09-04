# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.12)
project(ImportTxtPlugin)

find_package(Qt5 COMPONENTS Core Xml Qml Gui Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} MODULE
    importtxt.cpp
    importtxt.h
    plugin.json
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../core
    ${CMAKE_CURRENT_SOURCE_DIR}/../../skia
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Core
    Qt5::Xml
    Qt5::Qml
    Qt5::Gui
    Qt5::Widgets
    frictioncore
)

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/app/friction.app/Contents/MacOS/plugins
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/app/friction.app/Contents/MacOS/plugins
    )
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/app/plugins
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/app/plugins
    )
endif()

add_dependencies(all_friction_plugins ${PROJECT_NAME})
