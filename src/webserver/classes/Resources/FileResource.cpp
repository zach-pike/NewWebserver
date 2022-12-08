#include "FileResource.hpp"

#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>

FileResource::FileResource(std::string _filePath):
    filePath{_filePath} {}

FileResource::~FileResource() {}

HttpResponse FileResource::getResponse(const HttpRequest& req) {
    if (req.getMethod() != HttpRequest::Methods::GET) {
        // Make a text response
        return HttpResponse(403, "Wrong method");
    }
    
    std::ifstream f(filePath);

    if (f.bad()) {
        auto resp = HttpResponse(404, "Not found");
        const char* msg = "File could not be found";

        auto& headers = resp.getHeaders();

        headers.addHeader("content-type", "text/html");

        resp.setBody(std::vector<std::uint8_t>( msg, msg + strlen(msg)));

        return resp;
    } else {
        std::stringstream ss;
        ss << f.rdbuf();
        auto resp = HttpResponse(200, "Ok");

        auto& headers = resp.getHeaders();

        headers.addHeader("content-type", "text/html");

        std::string file = ss.str();

        resp.setBody(std::vector<std::uint8_t>(file.c_str(), file.c_str() + file.size()));

        return resp;
    }
}