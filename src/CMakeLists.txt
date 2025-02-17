cmake_minimum_required(VERSION 3.10)
project(file_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server 
    main.cpp
    start_server.cpp
    handle_client.cpp
    serve_file.cpp
    list_files.cpp
    cleanup_socket.cpp
)

if(WIN32)
    target_link_libraries(server ws2_32)
endif() 