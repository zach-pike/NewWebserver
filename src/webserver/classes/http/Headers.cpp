#include "Headers.hpp"

#include <algorithm>
#include <vector>

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

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

Headers::Headers() {}
Headers::~Headers() {}

void Headers::addHeader(std::string key, std::string value) {
    std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    headers.insert({ key, value });
}

std::string Headers::getHeader(std::string key) const {
    return headers.at(key);
}

std::string Headers::toString() const {
    std::string output = "";

    for (const auto& key : headers) {
        output += key.first + ": " + key.second + "\r\n";
    }

    output.erase(output.size() - 2);

    return output;
}

void Headers::parseFromString(std::string headersStr) {
    auto lines = split(headersStr, "\r\n");

    for (const auto& v : lines) {
        std::size_t seperator = v.find(':');

        std::string key = v.substr(0, seperator);
        trim(key);

        std::string value = v.substr(seperator + 1, v.size() - (seperator + 1));
        trim(value);

        addHeader(key, value);
    }
}

std::map<std::string, std::string>& Headers::asMap() {
    return headers;
}

bool Headers::hasHeader(std::string key) const {
    return headers.count(key) > 0;
}