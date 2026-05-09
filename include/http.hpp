#pragma once

#include <string>
#include <vector>
#include <memory>

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

class Request {
    public:
        Request(ReqType t, std::string p, Version v) : type(t), path(p), version(v) {};
        virtual ~Request();

        ReqType type;
        std::string path;
        Version version;

        virtual void parseHeader(const std::vector<std::string> &lines) = 0;
        virtual std::string buildResponse(const std::string &root, const std::vector<std::string> &body) = 0;

    private:
        std::string getPath(const std::string &line);
};

class GetRequest : public Request {
    public:
        GetRequest(std::string p, Version v) : Request(ReqType::GET, p, v) {}
        ~GetRequest() override = default;

        void parseHeader(const std::vector<std::string> &lines) override;
        std::string buildResponse(const std::string &root, const std::vector<std::string> &body) override;

    private:
        std::string readFile(const std::string &path);
};

class HeadRequest : public Request {
    public:
        HeadRequest(std::string p, Version v) : Request(ReqType::HEAD, p, v) {}
        ~HeadRequest() override = default; 

        void parseHeader(const std::vector<std::string> &lines) override;
        std::string buildResponse(const std::string &root, const std::vector<std::string> &body) override;

    private:
};

class PostRequest : public Request {
    public:
        PostRequest(std::string p, Version v) : Request(ReqType::POST, p, v) {}
        ~PostRequest() override = default;

        void parseHeader(const std::vector<std::string> &lines) override;
        std::string buildResponse(const std::string &root, const std::vector<std::string> &body) override;

    private:
};

class PutRequest : public Request {
    public:
        PutRequest(std::string p, Version v) : Request(ReqType::PUT, p, v) {}
        ~PutRequest() override = default; 

        void parseHeader(const std::vector<std::string> &lines) override;
        std::string buildResponse(const std::string &root, const std::vector<std::string> &body) override;

    private:
};

class DeleteRequest : public Request {
    public:
        DeleteRequest(std::string p, Version v) : Request(ReqType::DELETE, p, v) {} 
        ~DeleteRequest() override = default; 

        void parseHeader(const std::vector<std::string> &lines) override;
        std::string buildResponse(const std::string &root, const std::vector<std::string> &body) override;

    private:
};

class ConnectRequest : public Request {
    public:
        ConnectRequest(std::string p, Version v) : Request(ReqType::CONNECT, p, v) {}
        ~ConnectRequest() override = default; 

        void parseHeader(const std::vector<std::string> &lines) override;
        std::string buildResponse(const std::string &root, const std::vector<std::string> &body) override;

    private:
};

class OptionsRequest : public Request {
    public:
        OptionsRequest(std::string p, Version v) : Request(ReqType::OPTIONS, p, v) {}
        ~OptionsRequest() override = default; 

        void parseHeader(const std::vector<std::string> &lines) override;
        std::string buildResponse(const std::string &root, const std::vector<std::string> &body) override;

    private:
};

class TraceRequest : public Request {
    public:
        TraceRequest(std::string p, Version v) : Request(ReqType::TRACE, p, v) {}
        ~TraceRequest() override = default; 

        void parseHeader(const std::vector<std::string> &lines) override;
        std::string buildResponse(const std::string &root, const std::vector<std::string> &body) override;

    private:
};

class PatchRequest : public Request {
    public:
        PatchRequest(std::string p, Version v) : Request(ReqType::PATCH, p, v) {} 
        ~PatchRequest() override = default; 

        void parseHeader(const std::vector<std::string> &lines) override;
        std::string buildResponse(const std::string &root, const std::vector<std::string> &body) override;

    private:
};
    
std::unique_ptr<Request> parseRequestLine(const std::string &line);
