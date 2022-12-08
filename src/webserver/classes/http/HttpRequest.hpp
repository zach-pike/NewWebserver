#pragma once

#include <string>
#include <vector>
#include <cstdint>

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
    std::string path;
    Headers headers;
    std::vector<std::uint8_t> body;

    static Methods strToMethod(std::string method);
public:
    HttpRequest();
    ~HttpRequest();

    Headers getHeaders() const;

    void setBody(std::vector<std::uint8_t> v);

    // Include the final double CRLF in the buffer
    void parseHeader(const std::uint8_t* buffer, std::size_t length);

    Methods getMethod() const;
    std::string getPath() const;

    std::vector<std::uint8_t> getBody() const;
};