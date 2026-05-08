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
    Request(ReqType t, std::string p, float v) : type(t), path(p), version(v) {};
    virtual ~Request();

    ReqType type;
    std::string path;
    float version;

    std::string getPath(const std::string &line);
    virtual void parseHeader(const std::vector<std::string> &lines) = 0;
    virtual std::string buildResponse(std::vector<std::string> body) = 0;
};

struct GetRequest : Request {
    GetRequest(std::string p, float v) : Request(ReqType::GET, p, v) {}
    ~GetRequest() override = default;
    void parseHeader(const std::vector<std::string> &lines) override;
    std::string buildResponse(std::vector<std::string> body) override;
};

struct HeadRequest : Request {
    HeadRequest(std::string p, float v) : Request(ReqType::HEAD, p, v) {}
    ~HeadRequest() override = default; 
    void parseHeader(const std::vector<std::string> &lines) override;
    std::string buildResponse(std::vector<std::string> body) override;
};

struct PostRequest : Request {
    PostRequest(std::string p, float v) : Request(ReqType::POST, p, v) {}
    ~PostRequest() override = default;
    void parseHeader(const std::vector<std::string> &lines) override;
    std::string buildResponse(std::vector<std::string> body) override;
};

struct PutRequest : Request {
    PutRequest(std::string p, float v) : Request(ReqType::PUT, p, v) {}
    ~PutRequest() override = default; 
    void parseHeader(const std::vector<std::string> &lines) override;
    std::string buildResponse(std::vector<std::string> body) override;
};

struct DeleteRequest : Request {
    DeleteRequest(std::string p, float v) : Request(ReqType::DELETE, p, v) {} 
    ~DeleteRequest() override = default; 
    void parseHeader(const std::vector<std::string> &lines) override;
    std::string buildResponse(std::vector<std::string> body) override;
};

struct ConnectRequest : Request {
    ConnectRequest(std::string p, float v) : Request(ReqType::CONNECT, p, v) {}
    ~ConnectRequest() override = default; 
    void parseHeader(const std::vector<std::string> &lines) override;
    std::string buildResponse(std::vector<std::string> body) override;
};

struct OptionsRequest : Request {
    OptionsRequest(std::string p, float v) : Request(ReqType::OPTIONS, p, v) {}
    ~OptionsRequest() override = default; 
    void parseHeader(const std::vector<std::string> &lines) override;
    std::string buildResponse(std::vector<std::string> body) override;
};

struct TraceRequest : Request {
    TraceRequest(std::string p, float v) : Request(ReqType::TRACE, p, v) {}
    ~TraceRequest() override = default; 
    void parseHeader(const std::vector<std::string> &lines) override;
    std::string buildResponse(std::vector<std::string> body) override;
};

struct PatchRequest : Request {
    PatchRequest(std::string p, float v) : Request(ReqType::PATCH, p, v) {} 
    ~PatchRequest() override = default; 
    void parseHeader(const std::vector<std::string> &lines) override;
    std::string buildResponse(std::vector<std::string> body) override;
};
    
std::unique_ptr<Request> parseRequestLine(const std::string &line);
