#include "ResourceManager.hpp"
#include "Resources/TextResource.hpp"

#include <iostream>

#include <algorithm>
static std::vector<std::string> split(std::string const &str, const std::string& delim) {
    std::vector<std::string> tokens;
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
        end = str.find(delim, start);
        tokens.push_back(str.substr(start, end - start));
    }
    return tokens;
}

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {}

void ResourceManager::addResource(std::string path, std::shared_ptr<IResource> resource) {
    resources.insert({ path, resource });
}

static std::shared_ptr<IResource> sendResource(
    std::string path,
    std::map<std::string, std::shared_ptr<IResource>>& resources
) {
    if (resources.count(path) != 0) {
        return resources.at(path);
    }

    return std::make_shared<TextResource>("Not found", 404);
}

static bool stringStartsEndsWith(std::string str, char start, char end) {
    return *str.begin() == start && *(str.end() - 1) == end;
}

static std::shared_ptr<IResource> patternMatch(
    std::string path,
    std::map<std::string, std::shared_ptr<IResource>>& resources,
    std::string& resourceName
) {
    for (const auto& resource : resources) {
        if (stringStartsEndsWith(resource.first, '<', '>')) continue;
        auto parts = split(resource.first, "/");

        if (parts.size() == 0) {
            return sendResource("/", resources);
        } else {
            auto urlParts = split(path, "/");

            if (urlParts.size() != parts.size()) continue;

            for (int i = 0; i < urlParts.size(); i++) {
                if (urlParts[i] != parts[i] || stringStartsEndsWith(parts[i], '[', ']') == false) continue;
            }

            resourceName = resource.first;
            return resource.second;
        }
    }

    resourceName = "<None>";
    return sendResource("<NoResourceFound>", resources);
}

std::shared_ptr<IResource> ResourceManager::getResource(std::string path, std::string& resourceName) {
    return patternMatch(path, resources, resourceName);

}