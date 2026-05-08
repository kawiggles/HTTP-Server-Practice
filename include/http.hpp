#pragma once

#include <string>
#include <vector>
#include <memory>

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
    virtual ~Request() = default;

    ReqType type;
    std::string path;
    float version;

    std::string getPath(std::string line);
};

struct GetRequest : Request {};

struct HeadRequest : Request {};

struct PostRequest : Request {};

struct PutRequest : Request {};

struct DeleteRequest : Request {};

struct ConnectRequest : Request {};

struct OptionsRequest : Request {};

struct TraceRequest : Request {};

struct PatchRequest : Request {};
    
std::unique_ptr<Request> parseHeader(std::vector<std::string> &header);
