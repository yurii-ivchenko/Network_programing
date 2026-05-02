cmake_minimum_required(VERSION 3.10)

project(Individual2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SERVER_SOURCES 
    src/main_server.cpp 
    src/HornerServer.cpp
)

add_executable(server_app ${SERVER_SOURCES})

if(WIN32)
    target_link_libraries(server_app kernel32)
endif()

set(CLIENT_SOURCES 
    src/main_client.cpp
)

add_executable(client_app ${CLIENT_SOURCES})

if(WIN32)
    target_link_libraries(client_app kernel32)
endif()

if(WIN32)
    set_target_properties(server_app PROPERTIES SUFFIX ".exe")
    set_target_properties(client_app PROPERTIES SUFFIX ".exe")
endif()