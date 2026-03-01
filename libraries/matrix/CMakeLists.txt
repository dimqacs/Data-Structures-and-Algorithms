add_library(matrix STATIC
        matrix.c
)

target_include_directories(matrix
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(matrix
        PUBLIC
        read
        menu
        math
)