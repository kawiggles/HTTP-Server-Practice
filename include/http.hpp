#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class Server;

enum class Version {
    HTTP_09,
    HTTP_10,
    HTTP_11,
    HTTP_20,
    HTTP_30,
    INVALID
};

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

enum class Header {
    // Request Headers
    AUTHORIZATION,
    FROM,
    IF_MODIFIED_SINCE,
    REFERER,
    USERAGENT,
    HOST,
    ACCEPT,
    // Response Headers
    ALLOW,
    LOCATION,
    SERVER,
    EXPIRES,
    WWW_AUTHENTICATE,
    LAST_MODIFIED,
    // Common Headers
    DATE,
    PRAGMA,
    CONTENT_TYPE,
    CONTENT_LENGTH,
    CONTENT_ENCODING,
    CONNECTION,
    // Unknown
    UNKNOWN
};

Header getHeaderType(const std::string &header);

struct Response {
    std::string filecontent;
    std::unordered_map<Header, std::string> headers;
    Version version;
    std::string status;

    std::string generateResponseString();
    std::string generateHeaders();
};

class Request {
    public:
        Request(ReqType t, std::string p, Version v) : type(t), path(p), version(v) {};
        virtual ~Request();

        ReqType type;
        std::string path;
        Version version;
        std::unordered_map<Header, std::string> headers;

        void parseHeader(const std::vector<std::string> &lines);
        std::string readFile(const std::string &path);

        virtual Response buildResponse(const Server &server, const std::vector<std::string> &body) = 0;
        virtual std::string handlePath(const Server &server);
        virtual std::string getErrorCode() = 0;
};

class GetRequest : public Request {
    public:
        GetRequest(std::string p, Version v) : Request(ReqType::GET, p, v) {}
        ~GetRequest() override = default;

        Response buildResponse(const Server &server, const std::vector<std::string> &body) override;
};

class HeadRequest : public Request {
    public:
        HeadRequest(std::string p, Version v) : Request(ReqType::HEAD, p, v) {}
        ~HeadRequest() override = default; 

        Response buildResponse(const Server &server, const std::vector<std::string> &body) override;

    private:
};

class PostRequest : public Request {
    public:
        PostRequest(std::string p, Version v) : Request(ReqType::POST, p, v) {}
        ~PostRequest() override = default;

        Response buildResponse(const Server &server, const std::vector<std::string> &body) override;

    private:
};

class PutRequest : public Request {
    public:
        PutRequest(std::string p, Version v) : Request(ReqType::PUT, p, v) {}
        ~PutRequest() override = default; 

        Response buildResponse(const Server &server, const std::vector<std::string> &body) override;

    private:
};

class DeleteRequest : public Request {
    public:
        DeleteRequest(std::string p, Version v) : Request(ReqType::DELETE, p, v) {} 
        ~DeleteRequest() override = default; 

        Response buildResponse(const Server &server, const std::vector<std::string> &body) override;

    private:
};

class ConnectRequest : public Request {
    public:
        ConnectRequest(std::string p, Version v) : Request(ReqType::CONNECT, p, v) {}
        ~ConnectRequest() override = default; 

        Response buildResponse(const Server &server, const std::vector<std::string> &body) override;

    private:
};

class OptionsRequest : public Request {
    public:
        OptionsRequest(std::string p, Version v) : Request(ReqType::OPTIONS, p, v) {}
        ~OptionsRequest() override = default; 

        Response buildResponse(const Server &server, const std::vector<std::string> &body) override;

    private:
};

class TraceRequest : public Request {
    public:
        TraceRequest(std::string p, Version v) : Request(ReqType::TRACE, p, v) {}
        ~TraceRequest() override = default; 

        Response buildResponse(const Server &server, const std::vector<std::string> &body) override;

    private:
};

class PatchRequest : public Request {
    public:
        PatchRequest(std::string p, Version v) : Request(ReqType::PATCH, p, v) {} 
        ~PatchRequest() override = default; 

        Response buildResponse(const Server &server, const std::vector<std::string> &body) override;

    private:
};
    
std::unique_ptr<Request> parseRequestLine(const std::string &line);
