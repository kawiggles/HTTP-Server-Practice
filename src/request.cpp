#include "http.hpp"
#include "logs.hpp"

#include <regex>

ReqType getReqType(const std::string &type) {
    logMsg("Finding request type from buffer...");

    if (type.starts_with("GET"))            return ReqType::GET;
    else if (type.starts_with("HEAD"))      return ReqType::HEAD;
    else if (type.starts_with("POST"))      return ReqType::POST;
    else if (type.starts_with("PUT"))       return ReqType::PUT;
    else if (type.starts_with("DELETE"))    return ReqType::DELETE;
    else if (type.starts_with("CONNECT"))   return ReqType::CONNECT;
    else if (type.starts_with("OPTIONS"))   return ReqType::OPTIONS;
    else if (type.starts_with("TRACE"))     return ReqType::TRACE;
    else if (type.starts_with("PATCH"))     return ReqType::PATCH;
    else                                    return ReqType::INVALID;
}

std::string getPath(const std::string &line) {
    logMsg("Parsing request path in request line...");
    std::regex pathPattern("/([^ ]*)");
    std::smatch paths;
    std::regex_search(line, paths, pathPattern);
    return paths[0];
}

Request::~Request() = default;

std::unique_ptr<Request> parseRequestLine(const std::string &line) {
    logMsg("Parsing header with parseHeader()");

    float version;
    if (line.find("HTTP/") == std::string::npos) {
        if (line.starts_with("GET")) {
            logMsg("Request version is 0.9");
            version = 0.9;
        } else {
            logMsg("Error: request version not recognized");
            version = 0;
        }
    } else if (line.ends_with("0")) {
        logMsg("Request version is 1.0");
        version = 1.1;
    } else if (line.ends_with("1")) {
        logMsg("Request version is 1.1");
        version = 1.1;
    } else if (line.ends_with("2")) {
        logMsg("Request version is 2");
        version = 2;
    } else if (line.ends_with("3")) {
        logMsg("Request version is 3");
        version = 3;
    }

    std::string path = getPath(line);

    if (version != 0) {
        switch (getReqType(line)){
            case ReqType::GET: {
                logMsg("Request type is GET, parsing request path...");
                return std::make_unique<GetRequest>(path, version);
                break;
            }
            case ReqType::HEAD: {
                logMsg("Request type is GET, parsing request path...");
                return std::make_unique<HeadRequest>(path, version);
                break;
            }
            case ReqType::POST: {
                logMsg("Request type is POST, parsing request path...");
                return std::make_unique<PostRequest>(path, version);
                break;
            }
            case ReqType::PUT: {
                logMsg("Request type is PUT, parsing request path...");
                return std::make_unique<PutRequest>(path, version);
                break;
            }
            case ReqType::DELETE: {
                logMsg("Request type is DELETE, parsing request path...");
                return std::make_unique<DeleteRequest>(path, version);
                break;
            }
            case ReqType::CONNECT: {
                logMsg("Request type is CONNECT, parsing request path...");
                return std::make_unique<ConnectRequest>(path, version);
                break;
            }
            case ReqType::OPTIONS: {
                logMsg("Request type is OPTIONS, parsing request path...");
                return std::make_unique<OptionsRequest>(path, version);
                break;
            }
            case ReqType::TRACE: {
                logMsg("Request type is TRACE, parsing request path...");
                return std::make_unique<TraceRequest>(path, version);
                break;
            }
            case ReqType::PATCH: {
                logMsg("Request type is PATCH, parsing request path...");
                return std::make_unique<PatchRequest>(path, version);
                break;
            }
            case ReqType::INVALID:
                logMsg("Request type unrecognized");
                break;
        }
    }

    return nullptr;
}

void GetRequest::parseHeader(const std::vector<std::string> &lines) {
}

void HeadRequest::parseHeader(const std::vector<std::string> &lines) {
}

void PostRequest::parseHeader(const std::vector<std::string> &lines) {
}

void PutRequest::parseHeader(const std::vector<std::string> &lines) {
}

void DeleteRequest::parseHeader(const std::vector<std::string> &lines) {
}

void ConnectRequest::parseHeader(const std::vector<std::string> &lines) {
}

void OptionsRequest::parseHeader(const std::vector<std::string> &lines) {
}

void TraceRequest::parseHeader(const std::vector<std::string> &lines) {
}

void PatchRequest::parseHeader(const std::vector<std::string> &lines) {
}
