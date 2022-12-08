#include "webserver/Webserver.hpp"
#include "ResourceManagers/ResourceManager.hpp"
#include "Resources/FileResource.hpp"
#include "Resources/TextResource.hpp"

#include <iostream>

class MyResource : public IResource {
public:
    HttpResponse getResponse(const HttpRequest& req) {
        auto body = req.getBody();
        std::string text(body.begin(), body.end());

        std::cout << text << "\n";

        auto a = std::make_shared<TextResource>("Ok", 200);
        return a->getResponse(req);
    }
};

int main(int argc, char** argv) {
    auto controller = std::make_shared<ResourceManager>();

    controller->addResource("/", 
        std::make_shared<FileResource>("/home/zachary/webserver/src/index.html")
    );

    controller->addResource("/test", std::make_shared<MyResource>());

    controller->addResource("<404Page>",
        std::make_shared<TextResource>("Could not find page!", 404)
    );

    Webserver server(8080, "0.0.0.0");

    server.setResourceController(controller);

    if(!server.start([](std::string s){})) printf("Error\n");

    return 0;
}