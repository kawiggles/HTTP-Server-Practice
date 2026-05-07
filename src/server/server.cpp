#include "../logs.hpp"
#include "socket.hpp"
#include "server.hpp"

#include <thread>
#include <string>

extern "C" {
    void parseConfig(const char * path, ServerConfig * config);
}

Server::Server() {
    // We'll add these in later, once the haskell parser works
    // ServerConfig config;
    // parseConfig("config.toml", &config);
    
    s_sock = std::make_unique<Socket>(PORT);
}

void Server::run() {
    logMsg("Running Server Loop");
    while(true) {
        int clientFd = s_sock->sAccept();

        if (clientFd < 0) continue;

        std::thread t([&]() {
            this->handleClient(clientFd);
        });
        t.detach();
    }
}

void Server::handleClient(int clientFd) {
    logMsg("Running handleClient for client %d", clientFd);
    std::string buffer(BUFFER_SIZE, '\0');
    ssize_t bytes = recv(clientFd, buffer.data(), BUFFER_SIZE, 0);

    if (bytes > 0) {

    }
}
