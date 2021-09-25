#
# debug build from build dir: cmake -DCMAKE_BUILD_TYPE=Debug ..
#

cmake_minimum_required(VERSION 3.11...3.15)

### Set up for cross compilation ###
#include(./inc/arm-gcc-toolchain.cmake)

set (CMAKE_CXX_STANDARD 11)

project(main_project
         VERSION 0.1
         DESCRIPTION "Show the binary representation of a number, input in any base. Display things nicely."
         LANGUAGES CXX)

# FetchContent downloads during config step
include(FetchContent)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)

