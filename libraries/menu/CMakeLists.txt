add_library(menu STATIC
        menu.c
)

target_include_directories(menu
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)