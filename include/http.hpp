#pragma once

#include <string>
#include <vector>

enum class ReqType {
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH,
    INVALID
};

ReqType getReqType(const std::string &type);

struct Request {
    ReqType type;
    std::string path;
    float version;
};
    
Request parseHeader(std::vector<std::string> &header);
