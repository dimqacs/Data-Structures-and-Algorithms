cmake_minimum_required(VERSION 4.1)
project(dsa C)

set(CMAKE_C_STANDARD 11)

add_executable(dsa Laboratory1/main.c)

add_library(menu INTERFACE)
target_include_directories(menu INTERFACE Laboratory1/libraries)

target_link_libraries(dsa menu)
