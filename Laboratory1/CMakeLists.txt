add_executable(lab1
        main.c
        ../libraries/array.h
        ../libraries/read.h
)

target_include_directories(lab1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})