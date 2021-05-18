#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>

#include "post.h"

class Maze
{
public:
    Maze(std::string mazeNumber, size_t nLines, size_t nCols);

    size_t getNLines() const;
    size_t getNCols() const;
    std::vector<Post> &getExits();
    std::vector<Post> &getElectrified();
    std::vector<Post> &getNonElectrified();

private:
    size_t nCols;
    size_t nLines;
    std::vector<Post> exits;
    std::vector<Post> electrified;
    std::vector<Post> nonElectrified;
};

#endif