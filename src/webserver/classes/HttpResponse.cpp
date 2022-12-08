#include "HttpResponse.hpp"

#include <cstdint>

HttpResponse::HttpResponse(int _statusCode, std::string _statusMessage):
    statusCode{_statusCode},
    statusMessage{_statusMessage} {}

HttpResponse::~HttpResponse() {}

Headers& HttpResponse::getHeaders() {
    return headers;
}

void HttpResponse::setBody(std::vector<std::uint8_t> _body) {
    body = _body;
    headers.addHeader("content-length", std::to_string(body.size()));
}

std::vector<std::uint8_t> HttpResponse::toBytes() {
    std::string output = "HTTP/1.1 ";
    output += std::to_string(statusCode);
    output += " ";
    output += statusMessage;
    output += "\r\n";
    output += headers.toString();
    output += "\r\n\r\n";

    std::vector<std::uint8_t> outputBytes(output.c_str(), output.c_str() + output.size());
    outputBytes.insert(outputBytes.end(), body.begin(), body.end());

    return outputBytes;
}