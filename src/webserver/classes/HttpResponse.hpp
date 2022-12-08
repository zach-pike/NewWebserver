#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include "Headers.hpp"

class HttpResponse {
public:
private:
    std::vector<std::uint8_t> body;
    int statusCode = 200;
    std::string statusMessage = "Ok";

    Headers headers;
public:
    HttpResponse(int _statusCode, std::string _statusMessage);
    ~HttpResponse();

    Headers& getHeaders();

    void setBody(std::vector<std::uint8_t> _body);

    std::vector<std::uint8_t> toBytes();
};