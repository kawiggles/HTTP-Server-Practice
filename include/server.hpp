#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <climits>
#include <string>

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

        std::string root;
        std::string home = "/index.html";

        void run();

    private:
        int fd;
        sockaddr_in address;
        socklen_t addrlen = sizeof(address);

        void handleClient(int clientFd);
        int Accept();
};
