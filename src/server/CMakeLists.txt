add_library(server STATIC server.cpp server.hpp socket.cpp socket.hpp)

target_include_directories(net PUBLIC .)
