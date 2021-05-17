#include <string>

#include "util.h"

int sign(const long x)
{
    return (x > 0) - (x < 0);
}

bool isUtf8Byte1(const char c)
{
    // In a UTF8 encoded character, any byte after the first follows the pattern 0b10xxxxxx
    return ((c & 0b11000000) != 0b10000000);
}

size_t utf8Length(const std::string &str)
{
    size_t length = 0;

    for (char c : str)
        length += isUtf8Byte1(c);

    return length;
}