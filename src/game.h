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
    Game();
    ~Game();

    std::string getMazeNumber() const;
    std::chrono::steady_clock::time_point getStartTime() const;

    Result loadMaze(const std::string &mazeNumber);

    bool isGameOver() const;
    bool isPlayerAlive() const;
    Result movePlayer(int dx, int dy);
    void tick();
    void displayMaze();

private:
    std::string mazeNumber;
    std::chrono::steady_clock::time_point startTime;

    Maze *maze;
    Player *player;
    std::vector<Robot> robots;

    void reset();

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