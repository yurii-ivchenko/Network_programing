cmake_minimum_required(VERSION 3.10)
project(ClientServerApp)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# include files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(server src/Server.cpp src/Polynomial.cpp)
target_link_libraries(server ws2_32)

add_executable(client src/Client.cpp)
target_link_libraries(client ws2_32)
