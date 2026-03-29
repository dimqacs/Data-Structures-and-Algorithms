cmake_minimum_required(VERSION 3.25)
project(dsa C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Libraries
add_subdirectory(libraries/array)
add_subdirectory(libraries/menu)
add_subdirectory(libraries/read)
add_subdirectory(libraries/sort)
add_subdirectory(libraries/math)
add_subdirectory(libraries/matrix)
add_subdirectory(libraries/productArray)
add_subdirectory(libraries/file)
add_subdirectory(libraries/stack)
add_subdirectory(libraries/queue)

# Projects
add_subdirectory(Laboratory1) #Variant 5
add_subdirectory(Laboratory2) #Variant 5
add_subdirectory(Laboratory3) #Variant 5
add_subdirectory(Laboratory4) #Variant 3
add_subdirectory(Laboratory5) #Variant 22
add_subdirectory(Laboratory6) #Variant 13
