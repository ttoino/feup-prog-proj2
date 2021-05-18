#include <string>
#include <iostream>

#include "error.h"

Result::Result()
    : successful(true), errorMessage("") {}

Result::Result(std::string errorMessage)
    : successful(false), errorMessage(errorMessage) {}

Result::operator bool() const { return successful; }

std::ostream &operator<<(std::ostream &out, const Result &result)
{
    return out << result.errorMessage;
}