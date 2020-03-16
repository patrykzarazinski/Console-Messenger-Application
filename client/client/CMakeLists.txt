add_library(server include/client.h src/client.cpp)
target_include_directories(server PUBLIC include PRIVATE src)

target_link_libraries(server
    pthread
)
