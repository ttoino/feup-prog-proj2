// T01_G07

#ifndef PLAYER_H
#define PLAYER_H

#include <cstddef>

/**
 * This class represents the player
 */
class Player
{
public:
    /** 
     * Creates an alive player with the specified position
     * 
     * @param column The position on the x-axis
     * @param line The position on the y-axis
     */
    Player(unsigned int column, unsigned int line);

    /**
     * Update the player to be alive or dead
     * 
     * @param alive Whether the plyer is alive or dead
     */
    void setAlive(bool alive);

    /**
     * Updates the player's position
     * 
     * @param column The position on the x-axis
     * @param line The position on the y-axis
     */
    void setPosition(unsigned int column, unsigned int line);

    /** @returns Whether the player is alive or dead */
    bool isAlive() const;

    /** @returns The position on the y-axis */
    unsigned int getLine() const;

    /** @returns The position on the x-axis */
    unsigned int getColumn() const;

private:
    /** Whether the plyer is alive or dead */
    bool alive;

    /** Position on the x-axis */
    unsigned int column;

    /** Position on the y-axis */
    unsigned int line;
};
#endif