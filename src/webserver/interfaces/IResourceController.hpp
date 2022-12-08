#pragma once

#include <memory>
#include "IResource.hpp"

class IResourceController {
public:
    virtual std::shared_ptr<IResource> getResource(std::string path) = 0;
};