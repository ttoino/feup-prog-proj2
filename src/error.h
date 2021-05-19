#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>

using namespace std::literals;

const std::string GENERIC_ERROR = "Invalid input!"s;

const std::string RULES_NOT_FOUND = "Rules file not found"s;

const std::string CELL_OCCUPIED = "That cell is occupied!"s;
const std::string OUT_OF_BOUNDS = "Cannot move out of bounds!"s;

const std::string INVALID_MAZE_NUMBER = "Must be a number from 1 to 99!"s;
const std::string MAZE_NOT_FOUND = "That maze could not be found!"s;
const std::string INVALID_MAZE_HEADER_SIZE = "Invalid maze size in header!"s;
const std::string INVALID_MAZE_SIZE = "Maze does not match size in header!"s;
const std::string NO_PLAYER = "Maze has no players!"s;
const std::string NO_EXITS = "Maze has no exits!"s;
const std::string MULTIPLE_PLAYERS = "Maze has multiple players!"s;
const std::string INVALID_MAZE_CHARACTER = "Invalid character found in maze!"s;

const std::string INVALID_NAME = "Must have 15 characters or fewer!"s;
const std::string ANOTHER_NAME = ""s;

/**
 * This struct represents the result of a function that can have an error occur
 */
struct Result
{
    /** Use when the function was successful */
    Result();
    /** 
     * Use when the function was not successful
     * 
     * @param errorMessage The error message to show 
     */
    Result(std::string errorMessage);

    /** Whether the function was successful */
    bool successful;
    /** The error message to show if the function was unsuccessful */
    std::string errorMessage;

    /**
     * Convenience operator to convert this struct to a bool.
     * Equivelent to Result::successful
    */
    operator bool() const;
};

/**
 * Convenience operator to output the result's error message to a stream.
 */
std::ostream &operator<<(std::ostream &out, const Result &result);

#endif