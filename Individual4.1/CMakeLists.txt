cmake_minimum_required(VERSION 3.16)
project(UDPTimeService LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(time_server src/main_server.cpp src/TimeServer.cpp)
add_executable(time_client src/main_client.cpp src/TimeClient.cpp)

target_link_libraries(time_server ws2_32)
target_link_libraries(time_client ws2_32)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
