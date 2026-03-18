add_library(stack STATIC
        stack.c
)

target_include_directories(stack
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(stack
        PUBLIC
        menu
)