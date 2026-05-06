#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <climits>

#include "socket.hpp"

struct ServerConfig {
    int port;
    char path[PATH_MAX];
};

class Server {
    public:
        Server();
        ~Server ();

        Socket * s_sock = nullptr;

        void run();

    private:
        void handleClient();
};
