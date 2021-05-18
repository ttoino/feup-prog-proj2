#ifndef ERROR_H
#define ERROR_H

#include <string>

using namespace std::literals;

const std::string GENERIC_ERROR = "Invalid input!"s;

const std::string CELL_OCCUPIED = "That cell is occupied!"s;
const std::string OUT_OF_BOUNDS = "Cannot move out of bounds!"s;

const std::string INVALID_MAZE_NUMBER = "Must be a number from 1 to 99!"s;
const std::string MAZE_NOT_FOUND = "That maze could not be found!"s;
const std::string INVALID_MAZE_HEADER_SIZE = "Invalid maze size in header!"s;
const std::string INVALID_MAZE_SIZE = "Maze does not match size in header!"s;
const std::string NO_PLAYER = "Maze has no players!"s;
const std::string MULTIPLE_PLAYERS = "Maze has multiple players!"s;
const std::string INVALID_MAZE_CHARACTER = "Invalid character found in maze!"s;

const std::string INVALID_NAME = "Must have 15 characters or fewer!"s;
const std::string ANOTHER_NAME = "";

struct Result
{
    Result();
    Result(std::string errorMessage);

    const bool successful;
    const std::string errorMessage;

    operator bool() const;
    operator std::string() const;
};

#endif