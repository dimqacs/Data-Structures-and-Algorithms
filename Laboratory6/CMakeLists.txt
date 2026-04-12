add_executable(lab6
        main.c
)

target_link_libraries(lab6
        PRIVATE
        menu
        read
        productArray
        list
)
