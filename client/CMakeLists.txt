cmake_minimum_required(VERSION 3.14.5)
set (CMAKE_CXX_STANDARD 14)
project(client_app)

add_subdirectory(main_app)
add_subdirectory(client)
target_link_libraries(client socket)
