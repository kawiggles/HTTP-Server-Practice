cmake_minimum_required(VERSION 4.2.3)

project(HTTP_Server)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/server)
add_subdirectory(src/http)

add_executable(HTTP_Server main.cpp)

target_link_libraries(HTTP_Server PRIVATE http server)
