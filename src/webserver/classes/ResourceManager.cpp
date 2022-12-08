#include "ResourceManager.hpp"

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {}

void ResourceManager::addResource(std::string path, std::shared_ptr<IResource> resource) {
    resources.insert({ path, resource });
}

std::shared_ptr<IResource> ResourceManager::getResource(std::string path) {
    return resources.at(path);
}