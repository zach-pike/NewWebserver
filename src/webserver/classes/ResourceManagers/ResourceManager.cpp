#include "ResourceManager.hpp"

#include "Resources/TextResource.hpp"

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {}

void ResourceManager::addResource(std::string path, std::shared_ptr<IResource> resource) {
    resources.insert({ path, resource });
}

std::shared_ptr<IResource> ResourceManager::getResource(std::string path) {
    if (resources.count(path) == 0) {
        // Send a 404 resource if possible
        if (resources.count("<404Page>") != 0) {
            return resources.at("<404Page>");
        }

        // Make a text resource
        auto textresource = std::make_shared<TextResource>("Not found", 404);

        return textresource;
    }

    return resources.at(path);
}