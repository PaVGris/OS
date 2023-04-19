cmake_minimum_required(VERSION 3.21)
project(lab6_8)


add_executable(client
        src/client.cpp
        src/ZMQUtils.cpp
        src/message.cpp)
add_executable(server
        src/server.cpp
        src/ZMQUtils.cpp
        src/message.cpp)

target_link_libraries(server zmq)
target_link_libraries(client zmq)

target_include_directories(client PUBLIC include)
target_include_directories(server PUBLIC include)