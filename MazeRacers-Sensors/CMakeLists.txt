cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(Pico_ePaper_Code C CXX)
pico_sdk_init()

add_subdirectory(library/config)
add_subdirectory(library/devices)
add_subdirectory(library/objects)

include_directories(./library/config)
include_directories(./library/devices)
include_directories(./library/objects)

add_executable(main MazeRacers.cpp)

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

pico_add_extra_outputs(main)

target_link_libraries(main config pico_stdlib pico_stdlib devices hardware_i2c objects pico_multicore)
