#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <memory>

#include "IResourceController.hpp"

class Webserver {
private:
    std::uint16_t port = 80;
    std::string host;
    int serverfd;

    std::shared_ptr<IResourceController> controller;
public:
    Webserver(std::string _host, std::uint16_t _port);
    ~Webserver();

    void setResourceController(std::shared_ptr<IResourceController> _controller);

    bool start(std::function<void(std::string)> cb); // Bind and freeze main thread
};