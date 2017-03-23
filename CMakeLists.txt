cmake_minimum_required(VERSION 3.6)
project(ass1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES hide.c)
set(SOURCE_FILES unhide.c ppmHide.c ppmHide.h common.c common.h ppmCommon.c ppmCommon.h ppmUnhide.c ppmUnhide.h bmpCommon.c bmpCommon.h bmpHide.c bmpHide.h commonHide.c commonHide.h commonUnhide.c commonUnhide.h bmpUnhide.c bmpUnhide.h hide.h unhide.h)
add_executable(ass1 ${SOURCE_FILES} ppmHide.c ppmHide.h)