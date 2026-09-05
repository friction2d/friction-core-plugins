# SPDX-License-Identifier: GPL-3.0-only

add_custom_target(all_friction_plugins)

option(BUILD_PLG_HELLOWORLD "Build Hello World Plugin" OFF)
option(BUILD_PLG_IMPORTTXT "Build Import TXT Plugin" ON)
option(BUILD_PLG_LAUNCHERAPI "Build LauncherAPI Plugin" ON)

if(BUILD_PLG_HELLOWORLD)
    add_subdirectory(helloworld)
endif()

if(BUILD_PLG_IMPORTTXT)
    add_subdirectory(importtxt)
endif()

if(BUILD_PLG_LAUNCHERAPI)
    add_subdirectory(launcherapi)
endif()
