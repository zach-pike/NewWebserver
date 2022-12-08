#pragma once

#include "http/HttpResponse.hpp"
#include "http/HttpRequest.hpp"

class IResource {
public:
    virtual HttpResponse getResponse(const HttpRequest& req) = 0;
};