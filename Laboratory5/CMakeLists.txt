add_executable(lab5
        main.c
)

target_link_libraries(lab5
        PRIVATE
        menu
        read
        productArray
        file
        stack
)
