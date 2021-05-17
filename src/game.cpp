#include <vector>
#include <iostream>
#include <fstream>

#include "util.h"
#include "maze.h"
#include "player.h"
#include "robot.h"
#include "game.h"

using namespace std::literals;

Game::Game()
    : maze(nullptr), player(nullptr), robots{}
{
}

Game::~Game()
{
    if (maze)
        delete maze;

    if (player)
        delete player;
}

bool Game::loadMaze(const std::string &mazeNumber)
{
    // Open file
    std::ifstream file("MAZE_"s + mazeNumber + ".txt"s);

    // File doesn't exist
    if (!file.is_open())
    {
        // validInput = false;
        // errorMessage = MAZE_NOT_FOUND;
        return false;
    }

    // Get number of rows and columns from top of file
    char x;
    size_t nLines, nCols;
    file >> nLines >> x >> nCols;

    if (x != 'x' || file.fail())
    {
        // validInput = false;
        // errorMessage = INVALID_MAZE_HEADER_SIZE;
        return false;
    }

    maze = new Maze(mazeNumber, nLines, nCols);

    char c;
    size_t i = 0;
    while (file.get(c))
    {
        switch (c)
        {
        case '\n':
            // Ignore newlines
            continue;
        case 'R':
            robots.push_back(Robot(i % nCols, i / nCols));
            break;
        case 'H':
            if (player)
            {
                delete player;
                delete maze;
                robots = {};

                // Found two players
                // validInput = false;
                // errorMessage = MULTIPLE_PLAYERS;
                return false;
            }
            player = new Player(i % nCols, i / nCols);
            break;
        case ' ':
            // Ignore spaces
            break;
        case '*':
            maze->getElectrified().push_back(Post(i % nCols, i / nCols));
            break;
        case '+':
            maze->getNonElectrified().push_back(Post(i % nCols, i / nCols));
            break;
        case 'O':
            maze->getExits().push_back(Post(i % nCols, i / nCols));
            break;
        default:
            if (player)
                delete player;
            delete maze;
            robots = {};

            // Found an invalid character
            // validInput = false;
            // errorMessage = INVALID_MAZE_CHARACTER;
            return false;
        }

        i++;
    }

    if (!player)
    {
        delete maze;
        robots = {};

        // No player was found
        // validInput = false;
        // errorMessage = NO_PLAYER;
        return false;
    }

    // if (maze.nCols * maze.nLines != maze.fenceMap.size())
    // {
    //     // Size in header does not match maze size
    //     validInput = false;
    //     errorMessage = INVALID_MAZE_SIZE;
    //     return false;
    // }

    file.close();
    return true;
}

bool Game::isGameOver() const
{
    bool allDead = true;
    for (const Robot &robot : robots)
    {
        if (robot.isAlive())
        {
            allDead = false;
            break;
        }
    }

    return allDead || !player->isAlive();
}

bool Game::movePlayer(int dx, int dy)
{
    int newCol = player->getColumn() + dx;
    int newLine = player->getLine() + dy;

    if (newCol < 0 || newCol >= maze->getNCols() || newLine < 0 || newLine >= maze->getNLines())
    {
        return false;
    }

    // TODO

    player->setPosition(newCol, newLine);
    return true;
}

void Game::tick()
{
    // TODO
    // if (playerPostCollision() || playerRobotCollision())
    // {
    //     player->setAlive(false);
    //     return;
    // }

    moveRobots();
}

void Game::displayMaze()
{
    std::vector<char> visualMap(maze->getNCols() * maze->getNLines(), ' ');

    for (const Post &post : maze->getElectrified())
        visualMap.at(post.getLine() * maze->getNCols() + post.getColumn()) = '*';

    for (const Post &post : maze->getNonElectrified())
        visualMap.at(post.getLine() * maze->getNCols() + post.getColumn()) = '+';

    for (const Post &exit : maze->getExits())
        visualMap.at(exit.getLine() * maze->getNCols() + exit.getColumn()) = 'O';

    for (const Robot &robot : robots)
        visualMap.at(robot.getLine() * maze->getNCols() + robot.getColumn()) = robot.isAlive() ? 'R' : 'r';

    visualMap.at(player->getLine() * maze->getNCols() + player->getColumn()) = player->isAlive() ? 'H' : 'h';

    for (size_t i = 0; i < visualMap.size(); ++i)
    {
        std::cout << visualMap.at(i);

        if (i % maze->getNCols() == maze->getNCols() - 1)
            std::cout << '\n';
    }
}

void Game::moveRobots()
{
    for (Robot &robot : robots)
    {
        if (!robot.isAlive())
            continue;

        size_t newColumn = robot.getColumn() + sign(player->getColumn() - robot.getColumn());
        size_t newLine = robot.getLine() + sign(player->getLine() - robot.getLine());

        robot.moveRobot(newColumn, newLine);

        // TODO
        // robot.setAlive();

        for (Robot &other : robots)
        {
            if (&robot == &other)
                continue;

            if (robotRobotCollision(robot, other))
            {
                robot.setAlive(false);
                other.setAlive(false);
            }
        }
    }
}

// bool Game::playerPostCollision()
// {
//     // TODO
//     return false;
// }

// bool Game::playerRobotCollision()
// {
//     for (const Robot &robot : robots)
//     {
//         if (player->getLine() == robot.getLine() && player->getColumn() == robot.getColumn())
//             return true;
//     }
// }

// bool

bool Game::robotRobotCollision(const Robot &r1, const Robot &r2)
{
    return r1.getLine() == r2.getLine() && r1.getColumn() == r2.getColumn();
}

bool Game::electrifiedPostAt(size_t column, size_t line) const
{
    for (const Post &post : maze->getElectrified())
        if (post.getColumn() == column && post.getLine() == line)
            return true;

    return false;
}

bool Game::nonElectrifiedPostAt(size_t column, size_t line) const
{
    for (const Post &post : maze->getNonElectrified())
        if (post.getColumn() == column && post.getLine() == line)
            return true;

    return false;
}

bool Game::exitAt(size_t column, size_t line) const
{
    for (const Post &exit : maze->getExits())
        if (exit.getColumn() == column && exit.getLine() == line)
            return true;

    return false;
}

bool Game::deadRobotAt(size_t column, size_t line) const
{
    for (const Robot &robot : robots)
        if (!robot.isAlive() && robot.getColumn() == column && robot.getLine() == line)
            return true;

    return false;
}

bool Game::aliveRobotAt(size_t column, size_t line) const
{
    for (const Robot &robot : robots)
        if (robot.isAlive() && robot.getColumn() == column && robot.getLine() == line)
            return true;

    return false;
}
