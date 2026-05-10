#include "http.hpp"
#include "logs.hpp"
#include "server.hpp"

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

std::string Request::handlePath(const Server &server) {
    std::string absPath = "";
    absPath.append(server.root);
    if (path == "/")
        absPath.append(server.home);
    else
        absPath.append(path);

    return absPath;
}

std::string GetRequest::readFile(const std::string &path) {
    logMsg("Opening file at path %s", path.c_str());
    int file = open(path.c_str(), O_RDONLY);

    if (file < 0) {
        logMsg("Failed to open file at path %s: %s", path.c_str(), strerror(errno));
        return "error";
    }

    struct stat filestat;
    fstat(file, &filestat);

    std::string content;
    content.resize(filestat.st_size);
    logMsg("Reading file contents to memory...");
    if (read(file, content.data(), filestat.st_size) < 0) {
        logMsg("Failed to read file contents: %s", strerror(errno));
        return "error";
    }

    logMsg("Contents of file are:\n\n%s", content.c_str());
    return content;
}

Response GetRequest::buildResponse(const Server &server, const std::vector<std::string> &body) {
    logMsg("Building response for GET request");
    Response response;

    response.version = this->version;
    response.filecontent = readFile(handlePath(server));

    return response;
}

Response HeadRequest::buildResponse(const Server &server, const std::vector<std::string> &body) {
    logMsg("Building response for HEAD request");
    Response response;

    response.version = this->version;
    response.filecontent = "";

    return response;
}

Response PostRequest::buildResponse(const Server &server, const std::vector<std::string> &body) {
    logMsg("Building response for POST request");
    Response response;

    switch (version) {
        case Version::HTTP_09:
        case Version::HTTP_10:
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return response;
}

Response PutRequest::buildResponse(const Server &server, const std::vector<std::string> &body) {
    logMsg("Building response for PUT request");
    Response response;

    switch (version) {
        case Version::HTTP_09:
        case Version::HTTP_10:
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return response;
}

Response DeleteRequest::buildResponse(const Server &server, const std::vector<std::string> &body) {
    logMsg("Building response for DELETE request");
    Response response;

    switch (version) {
        case Version::HTTP_09:
        case Version::HTTP_10:
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return response;
}

Response ConnectRequest::buildResponse(const Server &server, const std::vector<std::string> &body) {
    logMsg("Building response for CONNECT request");
    Response response;

    switch (version) {
        case Version::HTTP_09:
        case Version::HTTP_10:
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return response;
}

Response OptionsRequest::buildResponse(const Server &server, const std::vector<std::string> &body) {
    logMsg("Building response for OPTIONS request");
    Response response;

    switch (version) {
        case Version::HTTP_09:
        case Version::HTTP_10:
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return response;
}

Response TraceRequest::buildResponse(const Server &server, const std::vector<std::string> &body) {
    logMsg("Building response for TRACE request");
    Response response;

    switch (version) {
        case Version::HTTP_09:
        case Version::HTTP_10:
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return response;
}

Response PatchRequest::buildResponse(const Server &server, const std::vector<std::string> &body) {
    logMsg("Building response for PATCH request");
    Response response;

    switch (version) {
        case Version::HTTP_09:
        case Version::HTTP_10:
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return response;
}
