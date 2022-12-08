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

    Headers& getHeaders();

    // Include the final double CRLF in the buffer
    void parseHeader(std::uint8_t* buffer, std::size_t length);

    Methods getMethod();
    std::string getPath();

    std::vector<std::uint8_t> getBody();
};