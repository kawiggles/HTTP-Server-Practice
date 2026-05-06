#include "../logs.hpp"
#include "socket.hpp"

#include <cerrno>
#include <cstring>

Socket::Socket(int port) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        logMsg("Socket constructor failed: %s", strerror(errno));
        exit(1);
    }

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        logMsg("Socket option setting failed: %s", strerror(errno));
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(fd, (struct sockaddr *)&address, addrlen) < 0) {
        logMsg("Socket bind failed: %s", strerror(errno));
        exit(1);
    }

    if (listen(fd, SOMAXCONN) < 0) {
        logMsg("Socket listen failed: %s", strerror(errno));
        exit(1);
    }
}

int Socket::sAccept() {
    int clientFd = accept(fd, (struct sockaddr *)&address, &addrlen);

    if (clientFd < 0) {
        logMsg("Socket sAccept() failed: %s", strerror(errno));
        return -1;
    }
    return clientFd;
}
