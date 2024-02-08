# set minimum required version of CMake
cmake_minimum_required(VERSION 3.27.8)

# include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# set project name and C/C++ standards
project(echo C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# create a pico-sdk subdirectory in project for libraries
pico_sdk_init()

# direct CMake to executable source file
add_executable(${PROJECT_NAME}
        echo.c
)

# create map/bin/hex/uf2 outputs
pico_add_extra_outputs(${PROJECT_NAME})

# link libraries
target_link_libraries(${PROJECT_NAME}
        pico_stdlib
)

# enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
