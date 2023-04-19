set(CMAKE_C_STANDARD 11)


set(CMAKE_THREAD_LIBS_INIT "-lpthread")
include_directories(include)
add_executable(Lab3
        include/library.h
        include/bitonic.h
        main.c
        src/bitonic.c
        )
target_include_directories(Lab3 PUBLIC include)
