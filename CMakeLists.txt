cmake_minimum_required(VERSION 4.2.3)

project(HTTP_Server)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src/server)
add_subdirectory(src/http)

add_executable(HTTP_Server main.cpp)

target_link_libraries(HTTP_Server PRIVATE http server)
