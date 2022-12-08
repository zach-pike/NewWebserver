#pragma once

#include "IResource.hpp"

class FileResource : public IResource {
private:
    std::string filePath;
public:
    FileResource(std::string _filePath);
    ~FileResource();
    
    std::unique_ptr<HttpResponse> getResponse(const HttpRequest& req);
};