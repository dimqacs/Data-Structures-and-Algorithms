cmake_minimum_required(VERSION 4.1)
project(sda C)

set(CMAKE_C_STANDARD 11)

add_executable(sda Laboratory1/main.c)

add_library(menu INTERFACE)
target_include_directories(menu INTERFACE Laboratory1/libraries)

target_link_libraries(sda menu)
