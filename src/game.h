#ifndef GAME_H
#define GAME_H

#include <vector>

#include "maze.h"
#include "player.h"
#include "robot.h"

class Game
{
public:
    Game();
    ~Game();

    bool loadMaze(const std::string &mazeNumber);

    bool isGameOver() const;
    bool movePlayer(int dx, int dy);
    void tick();
    void displayMaze();

private:
    Maze *maze;
    Player *player;
    std::vector<Robot> robots;

    void moveRobots();

    bool robotRobotCollision(const Robot &r1, const Robot &r2);
    bool playerRobotCollision(const Robot &robot);

    int electrifiedPostAt(size_t column, size_t line) const;
    int nonElectrifiedPostAt(size_t column, size_t line) const;
    int exitAt(size_t column, size_t line) const;
    int deadRobotAt(size_t column, size_t line) const;
    int aliveRobotAt(size_t column, size_t line) const;
};

#endif