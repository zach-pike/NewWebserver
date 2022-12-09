#pragma once

#include <memory>
#include "IResource.hpp"

class IResourceController {
public:
    virtual std::shared_ptr<IResource> getResource(std::string path, std::string& resourceName) = 0;
};