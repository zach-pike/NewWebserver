#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <memory>

#include "IResourceController.hpp"

class Webserver {
private:
    std::uint16_t port = 80;
    std::string host = "0.0.0.0";

    int serverfd;

    std::shared_ptr<IResourceController> controller;
public:
    Webserver(std::uint16_t _port, std::string _host);
    ~Webserver();

    void setResourceController(std::shared_ptr<IResourceController> _controller);

    bool start(std::function<void(std::string)> cb); // Bind and freeze main thread
};