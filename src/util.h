// T01_G07

#ifndef UTIL_H
#define UTIL_H

#include <string>

/**
 * Returns the sign of a number.
 * 
 * @param x The number to check
 * @returns 1 if x is positive, -1 if x is negative, 0 if x is 0
 */
int sign(const long x);

/**
 * Checks if a char represents the first byte in a UTF8 encoded character. 
 * (More specifically, checks if it does not represent any byte that is not the first, 
 * as those always follow the same pattern.)
 * 
 * @param c The byte to check
 * 
 * @returns Whether it is the first byte
 */
bool isUtf8Byte1(const char c);

/**
 * Counts the number of UTF8 encoded characters in a string. 
 * (More specifically, counts the number of bytes that represent the first byte of a UTF8 encoded character.)
 * 
 * @param str The string to get the length of
 * 
 * @returns The length of the string
 */
size_t utf8Length(const std::string &str);

/**
 * Normalizes input.
 * Replaces all tabs with spaces, removes duplicate spaces and trims spaces from the start and the end.
 *
 * @param input The input to normalize
 */
void normalizeInput(std::string &input);

/**
 * Gets a line from stdin, normalizes it, and returns false if the eof bit is set.
 *
 * @param input Where to store the input
 * @returns false if the eof bit is set, true otherwise
 */
bool getInput(std::string &input);

/**
 * Converts 2d position to index of 1d vector
 * 
 * @param column Position on the x-axis
 * @param line Position on the y-axis
 * @param nCols Size on the x-axis
 * 
 * @returns The index
 */
size_t toIndex(const size_t column, const size_t line, const size_t nCols);

#endif