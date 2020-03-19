add_library(socket include/socket.h src/socket.cpp)
target_include_directories(socket PUBLIC include PRIVATE src)

target_link_libraries(socket pthread)
