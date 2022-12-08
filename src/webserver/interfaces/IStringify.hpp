#pragma once

#include <string>

class IStringify {
public:
    virtual std::string toString() = 0;
};