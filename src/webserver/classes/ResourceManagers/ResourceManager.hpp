#pragma once

#include <memory>
#include <map>
#include <string>

#include "IResource.hpp"
#include "IResourceController.hpp"

class ResourceManager : public IResourceController {
private:
    std::map<std::string, std::shared_ptr<IResource>> resources;
public:
    ResourceManager();
    ~ResourceManager();

    std::shared_ptr<IResource> getResource(std::string path, std::string& resourceName);

    void addResource(std::string path, std::shared_ptr<IResource> resource);
};