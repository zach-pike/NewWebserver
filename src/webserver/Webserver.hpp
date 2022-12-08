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

    std::shared_ptr<IResourceController> controller;
public:
    Webserver(std::uint16_t _port, std::string _host);
    ~Webserver();

    void setController(std::shared_ptr<IResourceController> _controller);

    void start(std::function<void(std::string)> cb); // Bind and freeze main thread
};