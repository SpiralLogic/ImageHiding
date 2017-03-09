cmake_minimum_required(VERSION 3.6)
project(ass1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES encode.c)
add_executable(ass1 ${SOURCE_FILES})