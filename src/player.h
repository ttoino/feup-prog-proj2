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
    Player(size_t column, size_t line);

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
    void setPosition(size_t column, size_t line);

    /** @returns Whether the player is alive or dead */
    bool isAlive() const;

    /** @returns The position on the y-axis */
    size_t getLine() const;

    /** @returns The position on the x-axis */
    size_t getColumn() const;

private:
    /** Whether the plyer is alive or dead */
    bool alive;

    /** Position on the x-axis */
    size_t column;

    /** Position on the y-axis */
    size_t line;
};
#endif