cmake_minimum_required(VERSION 3.14.5)
set (CMAKE_CXX_STANDARD 14)
project(executeTests)

add_subdirectory(socket)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
target_link_libraries(${PROJECT_NAME} socket)
