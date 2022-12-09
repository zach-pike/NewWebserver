#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include <netinet/in.h>

#include "Headers.hpp"

class HttpRequest {
public:
    enum class Methods {
        GET,
        POST,
        PUT,
        PATCH,
        DELETE
    };
private:
    Methods method;
    std::string basePath;
    std::string fullPath;
    Headers headers;
    std::vector<std::uint8_t> body;

    std::map<std::string, std::string> queryParams;
    std::map<std::string, std::string> urlParams;

    static Methods strToMethod(std::string method);

    sockaddr_in clientAddress;
public:
    HttpRequest();
    ~HttpRequest();

    Headers getHeaders() const;

    void setBody(std::vector<std::uint8_t> v);

    // Include the final double CRLF in the buffer
    void parseHeader(const std::uint8_t* buffer, std::size_t length, sockaddr_in address);

    Methods getMethod() const;
    std::string getFullPath() const;

    // Path without query params or anything else
    std::string getBasePath() const;

    sockaddr_in getClientAddress() const;

    std::map<std::string, std::string> getQueryParams() const;
    std::map<std::string, std::string> getURLParams() const;
    void parseUrlParams(std::string resourcePath);

    std::vector<std::uint8_t> getBody() const;
};