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

    bool electrifiedPostAt(size_t column, size_t line) const;
    bool nonElectrifiedPostAt(size_t column, size_t line) const;
    bool exitAt(size_t column, size_t line) const;
    bool deadRobotAt(size_t column, size_t line) const;
    bool aliveRobotAt(size_t column, size_t line) const;
};

#endif