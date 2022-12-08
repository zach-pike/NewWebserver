#pragma once

#include <map>
#include <string>

#include "IStringify.hpp"

class Headers : public IStringify {
private:
    std::map<std::string, std::string> headers;
public:
    Headers();
    ~Headers();

    std::map<std::string, std::string>& asMap();

    bool hasHeader(std::string key) const;
    void addHeader(std::string key, std::string value);
    std::string getHeader(std::string key) const;

    void parseFromString(std::string headersStr);

    std::string toString() const;
};