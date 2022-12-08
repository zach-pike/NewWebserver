#include "webserver/Webserver.hpp"
#include "ResourceManager.hpp"
#include "FileResource.hpp"

#include <iostream>

int main(int argc, char** argv) {
    auto controller = std::make_shared<ResourceManager>();

    controller->addResource("/", 
        std::make_shared<FileResource>("/home/zachary/webserver/src/index.html")
    );

    std::string req = "GET / HTTP/1.1\r\nfirst-header: value\r\nsecond-header: value2\r\n\r\n";

    HttpRequest request;
    request.parseHeader((std::uint8_t*)req.c_str(), req.size());

    auto bytes = controller->
        getResource(request.getPath())->
        getResponse(request)->
        toBytes();

    std::string str(bytes.begin(), bytes.end());

    std::cout << str << std::endl;

    return 0;
}