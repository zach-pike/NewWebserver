#include "HttpRequest.hpp"

#include <algorithm>
static std::vector<std::string> split(std::string const &str, const std::string& delim) {
    std::vector<std::string> tokens;
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
        end = str.find(delim, start);
        tokens.push_back(str.substr(start, end - start));
    }
    return tokens;
}

HttpRequest::HttpRequest() {}
HttpRequest::~HttpRequest() {}

Headers HttpRequest::getHeaders() const {
    return headers;
}

HttpRequest::Methods HttpRequest::strToMethod(std::string str) {
    if (str == "GET") {
        return HttpRequest::Methods::GET;
    } else if (str == "POST") {
        return HttpRequest::Methods::POST;
    } else if (str == "PUT") {
        return HttpRequest::Methods::PUT;
    } else if (str == "PATCH") {
        return HttpRequest::Methods::PATCH;
    } else if (str == "DELETE") {
        return HttpRequest::Methods::DELETE;
    }

    return HttpRequest::Methods::GET;
}

void HttpRequest::parseHeader(const std::uint8_t* buffer, std::size_t length) {
    std::string requestString(buffer, buffer + length);

    requestString.erase(requestString.size() - 4);

    std::size_t firstCRLF = requestString.find("\r\n");


    std::string requestLine = requestString.substr(0, firstCRLF);
    std::string headersStr = requestString.substr(firstCRLF + 2, requestString.size() - (firstCRLF + 2));

    headers.parseFromString(headersStr);

    // Parse the request line
    auto requestLineParts = split(requestLine, " ");

    method = HttpRequest::strToMethod(requestLineParts[0]);
    path = requestLineParts[1];
}

HttpRequest::Methods HttpRequest::getMethod() const {
    return method;
}

std::string HttpRequest::getPath() const {
    return path;
}

std::vector<std::uint8_t> HttpRequest::getBody() const {
    return body;
}

void HttpRequest::setBody(std::vector<std::uint8_t> v) {
    body = v;
}