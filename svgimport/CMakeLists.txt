# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.12)
project(SvgImportPlugin)

friction_add_plugin(${PROJECT_NAME}
    svgimportplugin.cpp
    svganimationimportdialog.cpp
    svganimationimportdialog.h
    svganimationimporter.cpp
    svganimationimporter.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
    $<TARGET_PROPERTY:frictioncore,INCLUDE_DIRECTORIES>
)

target_link_directories(${PROJECT_NAME} PRIVATE
    $<TARGET_PROPERTY:frictioncore,LINK_DIRECTORIES>
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE skia user32 opengl32)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE skia-friction)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_RPATH "${CMAKE_BINARY_DIR}/src/core"
    )
endif()
