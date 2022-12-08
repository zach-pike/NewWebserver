#pragma once

#include "IResource.hpp"

class TextResource : public IResource {
private:
    std::string text;
    int code;
public:
    TextResource(std::string _text, int _code);
    ~TextResource();
    
    HttpResponse getResponse(const HttpRequest& req);
};