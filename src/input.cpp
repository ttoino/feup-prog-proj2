#include "input.h"
#include <string>
#include<iostream>

/**
 * Normalizes input.
 * Replaces all tabs with spaces, removes duplicate spaces and trims spaces from the start and the end.
 *
 * @param input The input to normalize
 */
void Input::normalizeInput(string& input)
{
    char last = 0;
    size_t i = 0;
    while (i < input.length())
    {
        char& c = input.at(i);

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

/**
 * Gets a line from stdin, normalizes it, and returns false if the eof bit is set.
 *
 * @param input Where to store the input
 * @returns false if the eof bit is set, true otherwise
 */
bool Input::getInput(string& input)
{
    getline(cin, input);
    normalizeInput(input);

    if (cin.eof())
        return false;

    return true;
}