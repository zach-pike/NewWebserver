#include "webserver/Webserver.hpp"
#include "ResourceManagers/ResourceManager.hpp"
#include "Resources/FileResource.hpp"
#include "Resources/TextResource.hpp"

#include "webutils/WebUtils.hpp"

#include <iostream>
#include <arpa/inet.h>
#include <string.h>

class MyResource : public IResource {
public:
    HttpResponse getResponse(const HttpRequest& req) {
        if (req.getMethod() != HttpRequest::Methods::POST)
            return TextResource("Wrong method", 403).getResponse(req);
        // Read the body into a 
        auto body = req.getBody();
        std::string text(body.begin(), body.end());

        std::cout << text << "\n";

        // Create a text resource and get the response
        return TextResource(req.getURLParams().at("item"), 200).getResponse(req);
    }
};

class TestResource : public IResource {
public:
    HttpResponse getResponse(const HttpRequest& req) {
        // Create a text resource and get the response
        auto urlparams = req.getURLParams();
        auto queryparams = req.getQueryParams();

        std::string f = "URL parameters:\n";

        for (const auto& param : urlparams) {
            f += param.first + ": " + param.second + "\n";
        }

        f += "\nQuery parameters:\n";

        for (const auto& param : queryparams) {
            f += param.first + ": " + param.second + "\n";
        }

        std::string ip = WebUtils::getIPFromSockAddr(req.getClientAddress());

        f += "\nClient IP: " + ip + ":" + std::to_string(htons(req.getClientAddress().sin_port));

        return TextResource(f, 200).getResponse(req);
    }
};

int main(int argc, char** argv) {
    // Make a new ResourceManager
    auto controller = std::make_shared<ResourceManager>();

    controller->addResource("/first/[item1]/[item2]", std::make_shared<TestResource>());
    controller->addResource("/test", std::make_shared<MyResource>());

    controller->addResource("<NoResourceFound>", std::make_shared<TextResource>("Could not find page!", 404));

    Webserver server("0.0.0.0", 8080);

    // RouteController
    server.setResourceController(controller);

    if(!server.start([](std::string s){
        std::cout << "Listening on: " << s << "\n";
    })) printf("Error\n");

    return 0;
}