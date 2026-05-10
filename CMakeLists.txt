cmake_minimum_required(VERSION 4.2.3)

project(HTTP_Server)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HTTP_Server main.cpp)

target_sources(HTTP_Server
    PRIVATE
        src/compose.cpp
        src/request.cpp
        src/response.cpp
        src/server.cpp

    PUBLIC
        FILE_SET headers
        TYPE HEADERS
        BASE_DIRS
            include
        FILES
            include/logs.hpp
            include/http.hpp
            include/server.hpp
)
