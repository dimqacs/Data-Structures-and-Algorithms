add_executable(lab1
        main.c
        array.h
)

target_include_directories(lab1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})