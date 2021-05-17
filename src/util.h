#include <string>

#ifndef UTIL_H
#define UTIL_H

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

#endif