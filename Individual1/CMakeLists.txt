cmake_minimum_required(VERSION 3.12)
project(PolynomialNetworkTask)

set(CMAKE_CXX_STANDARD 17)

# Додаємо шлях до заголовних файлів
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if(WIN32)
    set(NET_LIBS ws2_32)
endif()

# Вказуємо шлях src/ для головних файлів
add_executable(server_app 
    src/server_main.cpp 
    src/PolynomialLogic.cpp 
    src/NetworkBase.cpp
)
target_link_libraries(server_app PRIVATE ${NET_LIBS})

add_executable(client_app 
    src/client_main.cpp 
    src/NetworkBase.cpp
)
target_link_libraries(client_app PRIVATE ${NET_LIBS})