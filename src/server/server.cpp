#include "../logs.hpp"
#include "socket.hpp"
#include "server.hpp"

#include <thread>
#include <string>
#include <vector>

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
    // if \r\n\r\n, return should be ""
    auto getLine = [](std::string &buffer) {
        int endline = buffer.find('\n');
        std::string line = "";
        if (buffer[endline-1] == '\r')
            line = buffer.substr(0, endline);
        buffer = buffer.substr(endline + 1);
        return line;
    };

    logMsg("Running handleClient for client %d", clientFd);
    std::string buffer(BUFFER_SIZE, '\0');
    ssize_t bytes = recv(clientFd, buffer.data(), BUFFER_SIZE, 0);

    if (bytes > 0) {
        std::vector<std::string> header;
        std::string line = getLine(buffer);
        while (line != "") {
            header.push_back(line);
            line = getLine(buffer);
        }

        logMsg("Header received, parsing...");
        if (header[0].starts_with("GET") == 0 && header[0].ends_with("HTTP/1")) {
            logMsg("HTTP request is GET");
            int pathStart = header[0].find('/');
            std::string path = header[0].substr(pathStart, header[0].find(' ') - pathStart);
        }
    }
}
