#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <climits>
#include <memory>

#include "socket.hpp"

struct ServerConfig {
    int port;
    char path[PATH_MAX];
};

class Server {
    public:
        Server();
        ~Server () = default;

        std::unique_ptr<Socket> s_sock = nullptr;

        void run();
        void handleClient(int clientFd);
};
