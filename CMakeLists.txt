#  This Source Code Form is subject to the terms of the Mozilla Public
#  License, v. 2.0. If a copy of the MPL was not distributed with this
#  file, You can obtain one at https://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.15) # this hasn't been tested with lower CMake versions, but it might still work. just change this value to whatever version of CMake you have installed and give it a try!

project(parseinfix
    VERSION 0.1
    DESCRIPTION "An implementation of Dijkstra's shunting yard algorithm in C"
    LANGUAGES C
)

add_library(parseinfix
    parseinfix.h
    parseinfix.c
    stack.c
    stack.h
)
