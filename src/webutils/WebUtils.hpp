#pragma once

#include <arpa/inet.h>
#include <string>

namespace WebUtils {
    std::string getIPFromSockAddr(sockaddr_in s);
}