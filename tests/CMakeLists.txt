include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


set(CMAKE_CXX_STANDARD 17)

lab2
add_executable(lab2_test lab2_test.cpp
        ..lab2/include/library.h
        ..lab2/include/utils.h
        ..lab2/src/parent.c
        ..lab2/src/utils.c
        )

add_executable(child
        ..lab2/include/library.h
        ..lab2/include/utils.h
        ..lab2/src/child.c
        ..lab2/src/utils.c
        )

add_dependencies(lab2_test child)

target_include_directories(lab2_test PUBLIC include)



#lab3
add_executable(lab3_test lab3_test.cpp
	../lab3/src/bitonic.c
	../lab3/include/bitonic.h
   ../lab3/include/library.h)

target_link_libraries(lab3_test PRIVATE GTest::GTest)
target_include_directories(lab3_test PRIVATE ../lab3/include)

add_test(lab3_test lab3_test)




#lab4
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
add_executable(lab4_test
		lab4_test.cpp
		../lab4/src/pc.c
		../lab4/include/library.h
       )
target_link_libraries(lab4_test PRIVATE rt)
target_link_libraries(lab4_test PRIVATE GTest::GTest)
target_include_directories(lab4_test PRIVATE ../lab4/include)

add_test(lab4_test lab4_test)




#lab5
add_executable(lab5_1_test lab5_test.cpp
	../lab5/include/func.h
	../lab5/src/lib1.c )

target_link_libraries(lab5_1_test PRIVATE GTest::GTest)
target_include_directories(lab5_1_test PRIVATE ../lab5/include)

add_test(lab5_1_test lab5_1_test)

add_executable(lab5_2_test lab5_test.cpp
	../lab5/include/func.h
	../lab5/src/lib2.c )

target_link_libraries(lab5_2_test PRIVATE GTest::GTest)
target_include_directories(lab5_2_test PRIVATE ../lab5/include)

add_test(lab5_2_test lab5_2_test)
