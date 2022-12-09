#include "HttpRequest.hpp"

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

static void parseQuery(std::string query, std::map<std::string, std::string>& params) {
    query.erase(0, 1);

    auto pairs = split(query, "&");

    for (const auto& pair : pairs) {
        auto parts = split(pair, "=");

        if (parts.size() < 2) continue;

        std::string key = parts[0];
        std::string value = parts[1];

        trim(key);
        trim(value);

        params.insert({ key, value });
    }
}

HttpRequest::HttpRequest() {}
HttpRequest::~HttpRequest() {}

Headers HttpRequest::getHeaders() const {
    return headers;
}

HttpRequest::Methods HttpRequest::strToMethod(std::string str) {
    if (str == "GET") {
        return HttpRequest::Methods::GET;
    } else if (str == "POST") {
        return HttpRequest::Methods::POST;
    } else if (str == "PUT") {
        return HttpRequest::Methods::PUT;
    } else if (str == "PATCH") {
        return HttpRequest::Methods::PATCH;
    } else if (str == "DELETE") {
        return HttpRequest::Methods::DELETE;
    }

    return HttpRequest::Methods::GET;
}

void HttpRequest::parseHeader(const std::uint8_t* buffer, std::size_t length) {
    std::string requestString(buffer, buffer + length);

    requestString.erase(requestString.size() - 4);

    std::size_t firstCRLF = requestString.find("\r\n");


    std::string requestLine = requestString.substr(0, firstCRLF);
    std::string headersStr = requestString.substr(firstCRLF + 2, requestString.size() - (firstCRLF + 2));

    headers.parseFromString(headersStr);

    // Parse the request line
    auto requestLineParts = split(requestLine, " ");

    method = HttpRequest::strToMethod(requestLineParts[0]);
    fullPath = requestLineParts[1];

    // Parse the path into its parts

    // First check if there is any query parameters
    std::size_t queryStart = fullPath.find("?");

    if (queryStart != std::string::npos) {
        // Parse query params
        std::string queryParamsStr = fullPath.substr(queryStart, fullPath.size() - queryStart);

        parseQuery(queryParamsStr, queryParams);

        basePath = fullPath.substr(0, queryStart);
    } else {
        basePath = fullPath;
    }
}

HttpRequest::Methods HttpRequest::getMethod() const {
    return method;
}

std::string HttpRequest::getFullPath() const {
    return fullPath;
}

std::string HttpRequest::getBasePath() const {
    return basePath;
}

std::map<std::string, std::string> HttpRequest::getQueryParams() const {
    return queryParams;
}

std::vector<std::uint8_t> HttpRequest::getBody() const {
    return body;
}

void HttpRequest::setBody(std::vector<std::uint8_t> v) {
    body = v;
}