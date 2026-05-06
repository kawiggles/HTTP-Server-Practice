cmake_minimum_required(VERSION 4.2.3)

project(server)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

add_executable(server main.c)
