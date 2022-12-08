#pragma once

#include <memory>

#include "HttpResponse.hpp"
#include "HttpRequest.hpp"

class IResource {
public:
    virtual std::unique_ptr<HttpResponse> getResponse(const HttpRequest& req) = 0;
};