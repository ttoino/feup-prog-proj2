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
    /**Default constructor*/
    Game();

    /**Destructor, deletes the maze and the player information*/
    ~Game();

    /**@return return the number of the maze the player is playing*/
    std::string getMazeNumber() const;

    /**@return returns the time of the start of the game*/
    std::chrono::steady_clock::time_point getStartTime() const;

    /**
     * Loads a maze from the respective file.
     * Tries to handle invalid files.???
     *
     * @param mazeNumber 
     *
     * @returns _______________-
     */
    Result loadMaze(const std::string &mazeNumber);

    /**
     * Checks if the game has ended, either because the player reaches the exits or because the player is dead.
     *
     * @returns true if the game is over
     */
    bool isGameOver() const;

    /**
    * Checks if the player is still alive
    * 
    * @return returns true if the player is alive 
    */
    bool isPlayerAlive() const;

    /**
     * Receives the new movement of the player and moves accordingly
     * If it's invalid shows a helpful error message.
     * 
     * @returns ------------------
     */
    Result movePlayer(int dx, int dy);

    /**Moves the robots if the player is alive*/
    void tick();

    /**
     * Prints the maze's visualMap.
     *
     */
    void displayMaze();

private:

    /**A string with the number of the maze where the game is happening*/
    std::string mazeNumber;

    /**Starts the clock of the game*/
    std::chrono::steady_clock::time_point startTime;

    /**Pointer to the maze*/
    Maze *maze;
    /**Pointer to the player*/
    Player *player;
    /**Vector of the different robots and their features*/
    std::vector<Robot> robots;

    /**Starts over in case of some error*/
    void reset();

    /**
     * Moves the robots that are alive in sequential order.
     * Also checks for collisions between robots, robots and fences, and robots and the player.
     */
    void moveRobots();

    /**
     * Checks if two robots occupy the same cell.
     *
     * @param r1 The first robot
     * @param r2 The second robot
     *
     * @returns true if the robots collided
     */
    bool robotRobotCollision(const Robot &r1, const Robot &r2);

   /**
    * Checks if a robot and a player occupy the same cell.
    *
    * @param robot The robot
    *
    * @returns true if the entities collided
    */
    bool playerRobotCollision(const Robot &robot);

    /**
    * Checks if there's a eletrified post at the position given
    * 
    * @param column Position on the x-axis 
    * @param line Position on the y-axis 
    * 
    * @return index of the post in the maze vector or -1 if it wasn't found
    */
    int electrifiedPostAt(size_t column, size_t line) const;

    /**
    * Checks if there's a non-eletrified post at the position given
    *
    * @param column Position on the x-axis
    * @param line Position on the y-axis
    *
    * @return index of the post in the maze vector or -1 if it wasn't found
    */
    int nonElectrifiedPostAt(size_t column, size_t line) const;

    /**
    * Checks if there's a exit at the position given
    *
    * @param column Position on the x-axis
    * @param line Position on the y-axis
    *
    * @return index of the exit in the maze vector or -1 if it wasn't found
    */
    int exitAt(size_t column, size_t line) const;

    /**
    * Checks if there's a dead or stuck robot at the position given
    *
    * @param column Position on the x-axis
    * @param line Position on the y-axis
    *
    * @return index of the dead robot in the maze vector or -1 if it wasn't found
    */
    int deadRobotAt(size_t column, size_t line) const;

    /**
    * Checks if there's a alive robot at the position given
    *
    * @param column Position on the x-axis
    * @param line Position on the y-axis
    *
    * @return index of the alive robot in the maze vector or -1 if it wasn't found
    */
    int aliveRobotAt(size_t column, size_t line) const;
};

#endif