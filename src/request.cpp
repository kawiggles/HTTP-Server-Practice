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
    logMsg("Parsing request line with parseRequestLine()");
    logMsg("Request line is: %s", line.c_str());

    Version version;
    if (line.find("HTTP/") == std::string::npos) {
        if (line.starts_with("GET")) {
            logMsg("Request version is 0.9");
            version = Version::HTTP_09;
        } else {
            logMsg("Error: request version not recognized");
            version = Version::INVALID;
        }
    } else if (line.ends_with("0")) {
        logMsg("Request version is 1.0");
        version = Version::HTTP_10;
    } else if (line.ends_with("1")) {
        logMsg("Request version is 1.1");
        version = Version::HTTP_11;
    } else if (line.ends_with("2")) {
        logMsg("Request version is 2");
        version = Version::HTTP_20;
    } else if (line.ends_with("3")) {
        logMsg("Request version is 3");
        version = Version::HTTP_30;
    }

    std::string path = getPath(line);

    if (version != Version::INVALID) {
        switch (getReqType(line)){
            case ReqType::GET:
                logMsg("Request type is GET");
                return std::make_unique<GetRequest>(path, version);
            case ReqType::HEAD:
                logMsg("Request type is HEAD");
                return std::make_unique<HeadRequest>(path, version);
            case ReqType::POST:
                logMsg("Request type is POST");
                return std::make_unique<PostRequest>(path, version);
            case ReqType::PUT:
                logMsg("Request type is PUT");
                return std::make_unique<PutRequest>(path, version);
            case ReqType::DELETE:
                logMsg("Request type is DELETE");
                return std::make_unique<DeleteRequest>(path, version);
            case ReqType::CONNECT:
                logMsg("Request type is CONNECT");
                return std::make_unique<ConnectRequest>(path, version);
            case ReqType::OPTIONS:
                logMsg("Request type is OPTIONS");
                return std::make_unique<OptionsRequest>(path, version);
            case ReqType::TRACE:
                logMsg("Request type is TRACE");
                return std::make_unique<TraceRequest>(path, version);
            case ReqType::PATCH:
                logMsg("Request type is PATCH");
                return std::make_unique<PatchRequest>(path, version);
            case ReqType::INVALID:
                logMsg("Request type unrecognized");
                break;
        }
    }

    return nullptr;
}

void Request::parseHeader(const std::vector<std::string> &lines) {
    logMsg("Parsing remaining header with parseHeader()");
    logMsg("\nHeader content is:");
    for (const std::string &line : lines) {
        char colon = line.find(':');
        if (colon == std::string::npos) continue;
        Header key = getHeaderType(line.substr(0, colon));
        headers[key] = line.substr(colon + 2);
        logMsg("\t%s \t...%s", line.c_str(), (key == Header::UNKNOWN) ? "not recognized" : "parsed");
    }
}

Header getHeaderType(const std::string &header) {
    // Request Headers
    if (header == "Authorization")          return Header::AUTHORIZATION;
    else if (header == "From")              return Header::FROM;
    else if (header == "If-Modified-Since") return Header::IF_MODIFIED_SINCE;
    else if (header == "Referer")           return Header::REFERER;
    else if (header == "User-Agent")        return Header::USERAGENT;
    else if (header == "Host")              return Header::HOST;
    else if (header == "Accept")            return Header::ACCEPT;
    // Response Headers
    else if (header == "Allow")             return Header::ALLOW;
    else if (header == "Location")          return Header::LOCATION;
    else if (header == "Server")            return Header::SERVER;
    else if (header == "Expires")           return Header::EXPIRES;
    else if (header == "WWW-Authenticate")  return Header::WWW_AUTHENTICATE;
    else if (header == "Last-Modified")     return Header::LAST_MODIFIED;
    // Common Headers
    else if (header == "Date")              return Header::DATE;
    else if (header == "Pragma")            return Header::PRAGMA;
    else if (header == "Content-Type")      return Header::CONTENT_TYPE;
    else if (header == "Content-Length")    return Header::CONTENT_LENGTH;
    else if (header == "Content-Encoding")  return Header::CONTENT_ENCODING;
    else if (header == "Connection")        return Header::CONNECTION;
    // Unknown
    else                                    return Header::UNKNOWN;
}
