cmake_minimum_required(VERSION 3.14.5)
set (CMAKE_CXX_STANDARD 14)
project(server_app)

add_subdirectory(main_app)
add_subdirectory(server)
target_include_directories(server PUBLIC socket)
