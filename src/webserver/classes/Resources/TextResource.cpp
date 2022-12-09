#include "TextResource.hpp"

TextResource::TextResource(std::string _text, int _code):
    text{_text},
    code{_code} {}

TextResource::~TextResource() {}

HttpResponse TextResource::getResponse(const HttpRequest& req) {
    auto resp = HttpResponse(code, "Ok");

    resp.getHeaders().addHeader("content-type", "text/plain");
    resp.setBody(std::vector<std::uint8_t>(text.begin(), text.end()));

    return resp;
}