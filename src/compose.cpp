#include "http.hpp"

std::string Response::generateResponseString() {
    std::string content;

    switch (version) {
        case Version::HTTP_09:
            return filecontent;
        case Version::HTTP_10: {

        }
        case Version::HTTP_11: {
            content += "HTTP/1.1 ";
            content += status;
            content += "\r\n";

            // TODO: System for detecting and creating string for content type
            content += generateHeaders();
            content += "Content-Type: text/html\r\n";
            content += "Content-Length: " + std::to_string(filecontent.size()) + "\r\n";
            // TODO: System for determining whether to close connection
            content += "Connection: close\r\n";
            content += "\r\n";
            content.append(filecontent);
            return content;
        }
        case Version::HTTP_20:
        case Version::HTTP_30:
        case Version::INVALID:
            break;
    }

    return content;
}
