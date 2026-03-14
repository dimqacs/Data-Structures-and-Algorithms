add_library(file STATIC
        file.c
)

target_include_directories(file
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(file
        PUBLIC
        array
)