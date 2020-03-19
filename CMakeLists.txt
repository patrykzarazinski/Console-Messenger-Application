cmake_minimum_required(VERSION 3.14.5)
set (CMAKE_CXX_STANDARD 14)
project(Console_Application_Messenger)

add_subdirectory(server)
add_subdirectory(client)

add_subdirectory(tests)

add_subdirectory(socket)


