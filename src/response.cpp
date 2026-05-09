#include "http.hpp"
#include "logs.hpp"

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

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
    content.reserve(filestat.st_size);
    logMsg("Reading file contents to memory...");
    if (read(file, content.data(), filestat.st_size) < 0) {
        logMsg("Failed to read file contents: %s", strerror(errno));
        return "error";
    }

    logMsg("Contents of file are:\n\n%s", content.c_str());
    return content;
}

std::string GetRequest::buildResponse(const std::string &root, const std::vector<std::string> &body) {
    logMsg("Building response for GET request");
    std::string absPath = "";
    absPath.append(root);
    absPath.append(path);

    switch (version) {
        case Version::HTTP_09:
            return readFile(absPath);
        case Version::HTTP_10: {

        }
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return "error";
}

std::string HeadRequest::buildResponse(const std::string &root, const std::vector<std::string> &body) {
    logMsg("Building response for HEAD request");

    switch (version) {
        case Version::HTTP_09:
            return "error, request type not supported for this request version";
        case Version::HTTP_10:
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return "error";
}

std::string PostRequest::buildResponse(const std::string &root, const std::vector<std::string> &body) {
    logMsg("Building response for POST request");

    switch (version) {
        case Version::HTTP_09:
            return "error, request type not supported for this request version";
        case Version::HTTP_10:
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return "error";
}

std::string PutRequest::buildResponse(const std::string &root, const std::vector<std::string> &body) {
    logMsg("Building response for PUT request");

    switch (version) {
        case Version::HTTP_09:
            return "error, request type not supported for this request version";
        case Version::HTTP_10:
            return "error, request type not supported for this request version";
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return "error";
}

std::string DeleteRequest::buildResponse(const std::string &root, const std::vector<std::string> &body) {
    logMsg("Building response for DELETE request");

    switch (version) {
        case Version::HTTP_09:
            return "error, request type not supported for this request version";
        case Version::HTTP_10:
            return "error, request type not supported for this request version";
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return "error";
}

std::string ConnectRequest::buildResponse(const std::string &root, const std::vector<std::string> &body) {
    logMsg("Building response for CONNECT request");

    switch (version) {
        case Version::HTTP_09:
            return "error, request type not supported for this request version";
        case Version::HTTP_10:
            return "error, request type not supported for this request version";
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return "error";
}

std::string OptionsRequest::buildResponse(const std::string &root, const std::vector<std::string> &body) {
    logMsg("Building response for OPTIONS request");

    switch (version) {
        case Version::HTTP_09:
            return "error, request type not supported for this request version";
        case Version::HTTP_10:
            return "error, request type not supported for this request version";
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return "error";
}

std::string TraceRequest::buildResponse(const std::string &root, const std::vector<std::string> &body) {
    logMsg("Building response for TRACE request");

    switch (version) {
        case Version::HTTP_09:
            return "error, request type not supported for this request version";
        case Version::HTTP_10:
            return "error, request type not supported for this request version";
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return "error";
}

std::string PatchRequest::buildResponse(const std::string &root, const std::vector<std::string> &body) {
    logMsg("Building response for PATCH request");

    switch (version) {
        case Version::HTTP_09:
            return "error, request type not supported for this request version";
        case Version::HTTP_10:
            return "error, request type not supported for this request version";
        case Version::HTTP_11:
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return "error";
}
