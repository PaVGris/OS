set(CMAKE_THREAD_LIBS_INIT "-lpthread")
add_executable(lab4 main.c
		../lab4/src/pc.c
		../lab4/include/library.h
       )
target_link_libraries(lab4 PRIVATE rt)
target_include_directories(lab4 PRIVATE ../lab4/include)
