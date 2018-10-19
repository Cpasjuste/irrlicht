cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

# delete cmake cache folder before changing this option
set(BUILD_SDL2 OFF CACHE BOOL "Build with SDL2 support")
set(BUILD_VITA OFF CACHE BOOL "Build with PSP2 support")
set(BUILD_3DS OFF CACHE BOOL "Build with 3DS support")
set(BUILD_SWITCH ON CACHE BOOL "Build with NX (SWITCH) support")

include(Toolchain.cmake)

project(irrlicht)

##############
# irrlicht
##############
set(IRR_INC
        include
        source/Irrlicht
        )

file(GLOB IRR_SRC
        source/Irrlicht/*.cpp
        )

set(IRR_CFLAGS
        -D__SWITCH__
        -DNO_IRR_COMPILE_WITH_JOYSTICK_EVENTS_
        -DNO_IRR_COMPILE_WITH_X11_
        -DNO_IRR_COMPILE_WITH_CONSOLE_DEVICE_
        -DNO_IRR_COMPILE_WITH_SOFTWARE_
        -DNO_IRR_COMPILE_WITH_BURNINGSVIDEO_
)

set(IRR_LDFLAGS png z m)

#list(REMOVE_ITEM IRR_SRC ${CMAKE_SOURCE_DIR}/source/Irrlicht/CGLXManager.cpp)

#####################
# PLATORM SPECIFIC
#####################
if (BUILD_SWITCH)
    #####################
    # NX PLATORM
    #####################
    list(APPEND IRR_LDFLAGS glad EGL glapi drm_nouveau nx)
elseif (BUILD_SDL2)
    #####################
    # SDL2 PLATORM
    #####################
endif (BUILD_SWITCH)

#####################
# pplay executable
#####################
add_executable(${CMAKE_PROJECT_NAME}.elf ${IRR_SRC})
target_include_directories(${CMAKE_PROJECT_NAME}.elf PRIVATE ${IRR_INC})
target_compile_options(${CMAKE_PROJECT_NAME}.elf PRIVATE ${IRR_CFLAGS})
target_compile_options(${CMAKE_PROJECT_NAME}.elf PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>)
target_link_libraries(${CMAKE_PROJECT_NAME}.elf ${IRR_LDFLAGS})

