#include "logs.hpp"
#include "socket.hpp"
#include "server.hpp"
#include "http.hpp"

#include <thread>

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
        if (endline != std::string::npos) {
            int end = (endline > 0 && buffer[endline - 1] == '\r') ? endline - 1 : endline;
            line = buffer.substr(0, end);
            buffer = buffer.substr(endline + 1);
        }
        return line;
    };

    logMsg("Running handleClient for client %d", clientFd);
    std::string buffer(BUFFER_SIZE, '\0');
    ssize_t bytes = recv(clientFd, buffer.data(), BUFFER_SIZE, 0);

    if (bytes > 0) {
        logMsg("Header received, parsing...");
        std::unique_ptr<Request> request = parseRequestLine(getLine(buffer));

        std::vector<std::string> header;
        std::string line = getLine(buffer);
        while (line != "") {
            header.push_back(line);
            line = getLine(buffer);
        }

        request->parseHeader(header);

        std::vector<std::string> body;
        do {
            line = getLine(buffer);
            body.push_back(line);
        } while (line != "");

        request->buildResponse(body);
    }
}

