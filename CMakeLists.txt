cmake_minimum_required(VERSION 3.25)
project(dsa C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Libraries
add_subdirectory(libraries/array)
add_subdirectory(libraries/menu)
add_subdirectory(libraries/read)

# Projects
add_subdirectory(Laboratory1)
add_subdirectory(Laboratory2)
add_subdirectory(Laboratory3)
add_subdirectory(Laboratory4)
add_subdirectory(Laboratory5)
add_subdirectory(Laboratory6)
