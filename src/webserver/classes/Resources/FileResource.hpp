#pragma once

#include "IResource.hpp"

class FileResource : public IResource {
private:
    std::string filePath;
public:
    FileResource(std::string _filePath);
    ~FileResource();
    
    HttpResponse getResponse(const HttpRequest& req);
};