#include "WebUtils.hpp"

#include <string.h>

std::string WebUtils::getIPFromSockAddr(sockaddr_in s) {
    char buffer[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &s.sin_addr, buffer, INET_ADDRSTRLEN);

    return std::string(buffer, buffer + strlen(buffer));
}