add_executable(lab4
        main.c
)

target_link_libraries(lab4
        PRIVATE
        menu
        read
        sort
        productArray
        file
)
