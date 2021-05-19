#include <cstddef>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    
    /** Constructer, initializes de Player with their position
    * @param column The column of the player position
    * @param line The line of the player position
    */
    Player(size_t column, size_t line);

    /**
    * Change the state of the Player to false if the robot is dead
    * @param alive Boolian expression
    */
    void setAlive(bool alive);

    /**
    * Updates the position of the player to the parameters given
    * @param column Number of the new collun
    * @param line Number of the new line
    */
    void setPosition(size_t column, size_t line);

    /**
    * checks if the player is alive or dead
    * @return true if the player is alive, false if the player is dead
    */
    bool isAlive() const;

    /** @return returns the line of the player position at the moment*/
    size_t getLine() const;


    /** @return returns the column of the player position at the moment*/
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