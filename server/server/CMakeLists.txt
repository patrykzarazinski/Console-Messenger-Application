add_library(server include/server.h src/server.cpp include/socket.h src/socket.cpp)
target_include_directories(server PUBLIC include PRIVATE src)

target_link_libraries(server
    pthread
)
