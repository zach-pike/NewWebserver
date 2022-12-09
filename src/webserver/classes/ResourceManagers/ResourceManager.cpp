#include "ResourceManager.hpp"
#include "Resources/TextResource.hpp"

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
        // Remove control pages from the search
        if (stringStartsEndsWith(resource.first, '<', '>')) continue;

        // Get parts of path
        auto pathParts = split(path, "/");

        if (pathParts.size() == 0) {
            // If its empty then its just the / resource
            resourceName = "/";
            return sendResource("/", resources);
        }

        auto resourceParts = split(resource.first, "/");

        // If they arent the same length, then they
        // probably arent talking about the same resource
        if (pathParts.size() != resourceParts.size()) continue;
        
        bool notAMatch = false;

        for (int i = 0; i < pathParts.size(); i++) {
            // Check if the parts are the same or if the resourcePart has a url parameter
            if (!stringStartsEndsWith(resourceParts[i], '[', ']')) {
                if (pathParts[i] != resourceParts[i]) {
                    notAMatch = true;
                    break;
                }
            }
        }

        if (!notAMatch) {
            // If we got here, we have found a match
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