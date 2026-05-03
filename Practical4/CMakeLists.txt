cmake_minimum_required(VERSION 3.16)
project(PingWithIPHeaders LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Джерельні файли
set(SOURCES
    src/main.cpp
)

# Створюємо виконуваний файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Лінкуємо бібліотеку WinSock2
target_link_libraries(${PROJECT_NAME} ws2_32)

# Вивід інформації про збірку
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Source files: ${SOURCES}")

# Установлюємо папку для бінарників
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Додаємо опції компілятора для більш детальних попереджень
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()
