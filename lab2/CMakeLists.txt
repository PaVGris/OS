set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(Lab2
        include/library.h
        include/utils.h
        main.c
        src/parent.c
        src/utils.c
        )

add_executable(child
        include/library.h
        include/utils.h
        src/child.c
        src/utils.c
        )

add_dependencies(Lab2 child)

target_include_directories(Lab2 PUBLIC include)


