#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <climits>
#include <memory>

#define PORT 53545
#define BUFFER_SIZE 104857600

struct ServerConfig {
    int port;
    char path[PATH_MAX];
};

class Server {
    public:
        Server();
        ~Server () { if (fd >= 0) close(fd); }

        void run();
        void handleClient(int clientFd);

    private:
        int fd;
        sockaddr_in address;
        socklen_t addrlen = sizeof(address);

        int Accept();
};
