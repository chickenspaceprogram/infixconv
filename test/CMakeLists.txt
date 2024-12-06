#  This Source Code Form is subject to the terms of the Mozilla Public
#  License, v. 2.0. If a copy of the MPL was not distributed with this
#  file, You can obtain one at https://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.15)
project(parseinfix-tests C)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(../ ./parseinfix)

add_executable(TEST-stack
    tests/TEST-stack.c
)

target_link_libraries(TEST-stack parseinfix)

enable_testing()

add_test(
    NAME TEST-stack
    COMMAND $<TARGET_FILE:TEST-stack>
)