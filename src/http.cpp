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

Request parseHeader(std::vector<std::string> &header) {
    logMsg("Parsing header with parseHeader()");
    Request request;

    if (header[header.size() - 1].ends_with("9"))
        request.version = 0.9;
    else if (header[header.size() - 1].ends_with("0"))
        request.version = 1.1;
    else if (header[header.size() - 1].ends_with("1"))
        request.version = 1.1;
    else if (header[header.size() - 1].ends_with("2"))
        request.version = 2;
    else if (header[header.size() - 1].ends_with("3"))
        request.version = 3;
    else
        logMsg("Error: request version not recognized");

    request.type = getReqType(header[0]);

    switch (request.type){
        case ReqType::GET: {
            logMsg("Request type is GET, parsing request path...");
            std::regex pathPattern("/([^ ]*)");
            std::smatch paths;
            std::regex_search(header[0], paths, pathPattern);
            request.path = paths[0];
            break;
        }
        case ReqType::HEAD:
            logMsg("Request type is GET, parsing request path...");
            break;
        case ReqType::POST:
            logMsg("Request type is POST, parsing request path...");
            break;
        case ReqType::PUT:
            logMsg("Request type is PUT, parsing request path...");
            break;
        case ReqType::DELETE:
            logMsg("Request type is DELETE, parsing request path...");
            break;
        case ReqType::CONNECT:
            logMsg("Request type is CONNECT, parsing request path...");
            break;
        case ReqType::OPTIONS:
            logMsg("Request type is OPTIONS, parsing request path...");
            break;
        case ReqType::TRACE:
            logMsg("Request type is TRACE, parsing request path...");
            break;
        case ReqType::PATCH:
            logMsg("Request type is PATCH, parsing request path...");
            break;
        case ReqType::INVALID:
            logMsg("Request type unrecognized");
            break;
    }

    return request;
}
