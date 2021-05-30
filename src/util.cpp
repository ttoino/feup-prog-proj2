// T01_G07

#include <string>
#include <iostream>

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

void normalizeInput(std::string &input)
{
    char last = 0;
    size_t i = 0;
    while (i < input.length())
    {
        char &c = input.at(i);

        // Replace tabs with spaces
        if (c == '\t')
            c = ' ';

        // Delete character if it is a space at the begining, at the end or after another space
        if (c == ' ' && (last == ' ' || last == 0 || i == input.length() - 1 || i == 0))
        {
            input.erase(i, 1);

            // If we're outside the string, go back one
            if (i == input.length())
                i--;
        }
        else
        {
            i++;
            last = c;
        }
    }
}

bool getInput(std::string &input)
{
    std::getline(std::cin, input);
    normalizeInput(input);

    if (std::cin.eof())
        return false;

    return true;
}

size_t toIndex(const size_t column, const size_t line, const size_t nCols)
{
    return line * nCols + column;
}
