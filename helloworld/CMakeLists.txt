# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.12)
project(HelloWorldPlugin)

friction_add_plugin(${PROJECT_NAME}
    helloworld.cpp
    helloworld.h
)
