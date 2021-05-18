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
    return exitAt(player->getColumn(), player->getLine()) || !player->isAlive();
}

bool Game::isPlayerAlive() const
{
    return player->isAlive();
}

bool Game::movePlayer(int dx, int dy)
{
    int newCol = player->getColumn() + dx;
    int newLine = player->getLine() + dy;

    if (newCol < 0 || newCol >= maze->getNCols() || newLine < 0 || newLine >= maze->getNLines())
    {
        return false;
    }

    if (nonElectrifiedPostAt(newCol, newLine) >= 0 || deadRobotAt(newCol, newLine) >= 0)
        return false;

    if (electrifiedPostAt(newCol, newLine) >= 0)
    {
        player->setAlive(false);
        return true;
    }

    player->setPosition(newCol, newLine);
    return true;
}

void Game::tick()
{
    if (!player->isAlive())
        return;

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

        int i = electrifiedPostAt(newColumn, newLine);
        if (i >= 0)
        {
            robot.setAlive(false);

            auto electrified = maze->getElectrified();
            Post p = electrified.at(i);
            electrified.erase(electrified.begin() + i);
            maze->getNonElectrified().push_back(p);

            continue;
        }

        i = nonElectrifiedPostAt(newColumn, newLine);
        if (i >= 0)
        {
            robot.setAlive(false);
        }

        robot.moveRobot(newColumn, newLine);

        for (Robot &other : robots)
        {
            if (&robot == &other)
                continue;

            if (robotRobotCollision(robot, other))
            {
                robot.setAlive(false);
                other.setAlive(false);
            }

            if (playerRobotCollision(robot))
            {
                player->setAlive(false);
            }
        }
    }
}

bool Game::playerRobotCollision(const Robot &robot)
{
    return robot.getColumn() == player->getColumn() && robot.getLine() == player->getLine();
}

bool Game::robotRobotCollision(const Robot &r1, const Robot &r2)
{
    return r1.getLine() == r2.getLine() && r1.getColumn() == r2.getColumn();
}

int Game::electrifiedPostAt(size_t column, size_t line) const
{
    auto electrified = maze->getElectrified();
    for (size_t i = 0; i < electrified.size(); i++)
    {
        auto post = electrified.at(i);

        if (post.getColumn() == column && post.getLine() == line)
            return i;
    }

    return -1;
}

int Game::nonElectrifiedPostAt(size_t column, size_t line) const
{
    auto nonElectrified = maze->getNonElectrified();
    for (size_t i = 0; i < nonElectrified.size(); i++)
    {
        auto post = nonElectrified.at(i);

        if (post.getColumn() == column && post.getLine() == line)
            return i;
    }

    return -1;
}

int Game::exitAt(size_t column, size_t line) const
{
    auto exits = maze->getExits();
    for (size_t i = 0; i < exits.size(); i++)
    {
        auto exit = exits.at(i);

        if (exit.getColumn() == column && exit.getLine() == line)
            return i;
    }

    return -1;
}

int Game::deadRobotAt(size_t column, size_t line) const
{
    for (size_t i = 0; i < robots.size(); i++)
    {
        auto robot = robots.at(i);

        if (!robot.isAlive() && robot.getColumn() == column && robot.getLine() == line)
            return i;
    }

    return -1;
}

int Game::aliveRobotAt(size_t column, size_t line) const
{
    for (size_t i = 0; i < robots.size(); i++)
    {
        auto robot = robots.at(i);

        if (robot.isAlive() && robot.getColumn() == column && robot.getLine() == line)
            return i;
    }

    return -1;
}
