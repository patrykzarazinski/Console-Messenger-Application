add_library(client include/client.h src/client.cpp)
target_include_directories(client PUBLIC include PRIVATE src)

target_link_libraries(client
    pthread
)
