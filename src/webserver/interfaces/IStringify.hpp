#pragma once

#include <string>

class IStringify {
public:
    virtual std::string toString() const = 0;
};