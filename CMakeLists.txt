cmake_minimum_required(VERSION 3.6)
project(ass1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES hide.c)
set(SOURCE_FILES unhide.c ppmHide.c ppmHide.h common.c common.h ppmCommon.c ppmCommon.h ppmUnhide.c ppmUnhide.h)
add_executable(ass1 ${SOURCE_FILES} ppmHide.c ppmHide.h)