#include "maze.h"

Maze::Maze(std::string mazeNumber, size_t nLines, size_t nCols)
{
    this->mazeNumber = mazeNumber;
    this->nLines = nLines;
    this->nCols = nCols;
}

std::string Maze::getMazeNumber() const
{
    return mazeNumber;
}

size_t Maze::getNLines() const
{
    return nLines;
}

size_t Maze::getNCols() const
{
    return nCols;
}

std::vector<Post> &Maze::getExits()
{
    return exits;
}

std::vector<Post> &Maze::getElectrified()
{
    return electrified;
}

std::vector<Post> &Maze::getNonElectrified()
{
    return nonElectrified;
}
