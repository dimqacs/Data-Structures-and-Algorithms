add_executable(lab2
        main.c
)

target_link_libraries(lab2
        PRIVATE
        menu
        read
        sort
        array
        productArray
)
