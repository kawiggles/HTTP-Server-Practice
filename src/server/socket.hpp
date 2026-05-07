#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 53545
#define BUFFER_SIZE 104857600

class Socket {
    public:
        Socket(int port);
        ~Socket() { if (fd >=0) close(fd); }

        Socket(const Socket &) = delete; // Don't allow Socket a = b
        Socket & operator = (const Socket &) = delete; // Don't allow a = b, where a is already a Socket
        Socket(Socket && other) noexcept :
            fd(other.fd), address(other.address), addrlen(other.addrlen) {
                other.fd = -1;
        } // Handles rvalue Sockets, like Socket a = Socket(8000)
        
        int sAccept();
    private:
        int fd; // File Descriptor
        socklen_t addrlen = sizeof(address);
        sockaddr_in address;
};
