// T01_G07

#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>

#include "post.h"

/**
 * This class represents a maze
 */
class Maze
{
public:
    /** 
     * Creates an empty maze with the specified size
     * 
     * @param nLines The size of the maze on the x-axis
     * @param nCols The size of the maze on the y-axis
     */
    Maze(size_t nLines, size_t nCols);

    /** @returns The size of the maze on the x-axis */
    size_t getNCols() const;
    /** @returns The size of the maze on the y-axis */
    size_t getNLines() const;
    /** @returns A vector holding this maze's exits */
    std::vector<Post> &getExits();
    /** @returns A vector holding this maze's electrified posts */
    std::vector<Post> &getElectrified();
    /** @returns A vector holding this maze's non electrified posts */
    std::vector<Post> &getNonElectrified();

private:
    /** Size of the maze on the x-axis */
    size_t nCols;
    /** Size of the maze on the y-axis */
    size_t nLines;
    /** Vector holding this maze's exits */
    std::vector<Post> exits;
    /** Vector holding this maze's electrified posts */
    std::vector<Post> electrified;
    /** Vector holding this maze's non electrified posts */
    std::vector<Post> nonElectrified;
};

#endif