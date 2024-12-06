#  This Source Code Form is subject to the terms of the Mozilla Public
#  License, v. 2.0. If a copy of the MPL was not distributed with this
#  file, You can obtain one at https://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.15) # this hasn't been tested with lower CMake versions, but it might still work. just change this value to whatever version of CMake you have installed and give it a try!

project(stack-like C)

add_library(stack-like
    queue.h
    queue.c
    stack-like.c
    stack-like.h
    stack.c
    stack.h
)