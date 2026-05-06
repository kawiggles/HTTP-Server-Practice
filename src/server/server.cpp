#include "../logs.hpp"
#include "socket.hpp"
#include "server.hpp"

#include <cerrno>
#include <cstring>
#include <thread>

extern "C" {
    void parseConfig(const char * path, ServerConfig * config);
}

Server::Server() {
    ServerConfig config;
    parseConfig("config.toml", &config);

}

void Server::run() {
    logMsg("Running Server Loop");
    while(true) {
        int clientFd = s_sock->sAccept();
        ASSERT(clientFd >= 0);
        std::thread(&Server::handleClient, *this);
    }
}
