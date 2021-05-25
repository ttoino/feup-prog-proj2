// T01_G07

#include "maze.h"

Maze::Maze(size_t nLines, size_t nCols)
    : nLines(nLines), nCols(nCols) {}

size_t Maze::getNLines() const { return nLines; }

size_t Maze::getNCols() const { return nCols; }

std::vector<Post> &Maze::getExits() { return exits; }

std::vector<Post> &Maze::getElectrified() { return electrified; }

std::vector<Post> &Maze::getNonElectrified() { return nonElectrified; }
