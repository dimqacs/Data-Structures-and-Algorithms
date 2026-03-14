add_executable(lab3
        main.c
)

target_link_libraries(lab3
        PRIVATE
        menu
        read
        sort
        productArray
        file
)
