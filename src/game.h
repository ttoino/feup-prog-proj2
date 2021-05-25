// T01_G07

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <chrono>

#include "error.h"
#include "maze.h"
#include "player.h"
#include "robot.h"
#include "leaderboard.h"

class Game
{
public:
    /** Default constructor */
    Game();

    /**Destructor, deletes the maze and the player information*/
    ~Game();

    /** @returns The number of the maze the player is playing */
    std::string getMazeNumber() const;

    /** @returns When the game started */
    std::chrono::steady_clock::time_point getStartTime() const;

    /**
     * Loads a maze from the respective file. 
     * Sets all relevant properties, including the maze number. 
     * Tries to handle invalid files.
     *
     * @param mazeNumber The number of the maze to load (in the range "01" to "99")
     *
     * @returns A Result object. See its documentation for more info
     */
    Result loadMaze(const std::string &mazeNumber);

    /**
     * Checks if the game has ended, either because the player's reached the exits or because the player is dead.
     *
     * @returns Whether the game is over
     */
    bool isGameOver() const;

    /**
    * Checks if the player is still alive
    * 
    * @returns Whether the player is alive 
    */
    bool isPlayerAlive() const;

    /**
     * Moves the player in the specified direction. 
     * Is unsuccessful if the movement is invalid
     * 
     * @param dx How many cells to move in the x axis
     * @param dy How many cells to move in the y axis
     * 
     * @returns A Result object. See its documentation for more info
     */
    Result movePlayer(int dx, int dy);

    /** Moves the robots if the player is alive */
    void tick();

    /** Prints the game's current state to stdout */
    void displayMaze();

private:
    /** The number of the maze the player is playing */
    std::string mazeNumber;

    /** When the game started */
    std::chrono::steady_clock::time_point startTime;

    /** Pointer to the current maze */
    Maze *maze;
    /** Pointer to the player */
    Player *player;
    /** A vector holding all the robots */
    std::vector<Robot> robots;

    /** Reset all properties */
    void reset();

    /**
     * Moves the robots that are alive in sequential order.
     * Also checks for collisions between robots, robots and fences, and robots and the player.
     */
    void moveRobots();

    /**
     * Checks if two robots occupy the same cell
     *
     * @param r1 The first robot
     * @param r2 The second robot
     *
     * @returns true if the robots collided
     */
    bool robotRobotCollision(const Robot &r1, const Robot &r2);

    /**
    * Checks if a robot occupies the same cell as the player
    *
    * @param robot The robot
    *
    * @returns true if the entities collided
    */
    bool playerRobotCollision(const Robot &robot);

    /**
    * Checks if there's an electrified post at the position given
    * 
    * @param column Position on the x-axis 
    * @param line Position on the y-axis 
    * 
    * @return index of the post or -1 if it wasn't found
    */
    int electrifiedPostAt(size_t column, size_t line) const;

    /**
    * Checks if there's a non-electrified post at the position given
    *
    * @param column Position on the x-axis
    * @param line Position on the y-axis
    *
    * @return index of the post or -1 if it wasn't found
    */
    int nonElectrifiedPostAt(size_t column, size_t line) const;

    /**
    * Checks if there's an exit at the position given
    *
    * @param column Position on the x-axis
    * @param line Position on the y-axis
    *
    * @return index of the exit or -1 if it wasn't found
    */
    int exitAt(size_t column, size_t line) const;

    /**
    * Checks if there's a dead or stuck robot at the position given
    *
    * @param column Position on the x-axis
    * @param line Position on the y-axis
    *
    * @return index of the dead robot or -1 if it wasn't found
    */
    int deadRobotAt(size_t column, size_t line) const;

    /**
    * Checks if there's an alive robot at the position given
    *
    * @param column Position on the x-axis
    * @param line Position on the y-axis
    *
    * @return index of the alive robot or -1 if it wasn't found
    */
    int aliveRobotAt(size_t column, size_t line) const;
};

#endif