cmake_minimum_required(VERSION 3.16)
project(NetworkProgramming LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(icmp_app src/main_icmp.cpp src/ICMPApp.cpp)
add_executable(igmp_client src/main_igmp.cpp src/IGMPApp.cpp)
add_executable(igmp_server src/main_igmp_server.cpp src/IGMPServer.cpp)

target_link_libraries(icmp_app ws2_32)
target_link_libraries(igmp_client ws2_32)
target_link_libraries(igmp_server ws2_32)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
