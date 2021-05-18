#include <string>

#include "error.h"

Result::Result()
    : successful(true), errorMessage("") {}

Result::Result(std::string errorMessage)
    : successful(false), errorMessage(errorMessage) {}

Result::operator bool() const { return successful; }

Result::operator std::string() const { return errorMessage; }