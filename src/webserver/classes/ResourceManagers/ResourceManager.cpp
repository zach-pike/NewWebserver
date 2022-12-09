#include "ResourceManager.hpp"

#include "Resources/TextResource.hpp"

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {}

void ResourceManager::addResource(std::string path, std::shared_ptr<IResource> resource) {
    resources.insert({ path, resource });
}


static std::shared_ptr<IResource> patternMatch(
    std::string path,
    std::map<std::string, std::shared_ptr<IResource>>& resources
) {
    for (const auto& resource : resources) {

    }

    if (resources.count("<NoResourceFound>") != 0) {
        return resources.at("<NoResourceFound>");
    }

    return std::make_shared<TextResource>("Not found", 404);
}

std::shared_ptr<IResource> ResourceManager::getResource(std::string path) {
    return patternMatch(path, resources);
}