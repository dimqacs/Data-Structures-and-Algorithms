add_library(read STATIC
        read.c
)

target_include_directories(read
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)