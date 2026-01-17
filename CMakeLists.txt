cmake_minimum_required(VERSION 4.1)
project(dsa C)

set(CMAKE_C_STANDARD 11)

add_executable(dsa Laboratory1/main.c
        Laboratory1/libraries/array.h)
