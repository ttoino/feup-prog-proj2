// T01_G07

#include "maze.h"

Maze::Maze(unsigned int nLines, unsigned int nCols)
    : nLines(nLines), nCols(nCols) {}

unsigned int Maze::getNLines() const { return nLines; }

unsigned int Maze::getNCols() const { return nCols; }

std::vector<Post> &Maze::getExits() { return exits; }

std::vector<Post> &Maze::getElectrified() { return electrified; }

std::vector<Post> &Maze::getNonElectrified() { return nonElectrified; }
