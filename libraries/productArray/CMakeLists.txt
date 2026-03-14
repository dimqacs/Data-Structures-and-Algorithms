add_library(productArray STATIC
        productArray.c
)

target_include_directories(productArray
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(productArray
        PUBLIC
        array
        read
        menu
)