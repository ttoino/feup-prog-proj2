// T01_G07

#include <vector>
#include <iostream>
#include <fstream>

#include "util.h"
#include "error.h"
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

std::string Game::getMazeNumber() const { return mazeNumber; }

std::chrono::steady_clock::time_point Game::getStartTime() const { return startTime; }

Result Game::loadMaze(const std::string &mazeNumber)
{
    reset();

    // Open file
    std::ifstream file("MAZE_"s + mazeNumber + ".txt"s);

    // File doesn't exist
    if (!file.is_open())
        return {MAZE_NOT_FOUND};

    // Get number of rows and columns from top of file
    char x;
    size_t nLines, nCols;
    file >> nLines >> x >> nCols;

    if (x != 'x' || file.fail())
        return {INVALID_MAZE_HEADER_SIZE};

    maze = new Maze(nLines, nCols);

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
                return {MULTIPLE_PLAYERS};

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
            // Found an invalid character
            return {INVALID_MAZE_CHARACTER};
        }

        i++;
    }

    if (!player)
        // No player was found
        return {NO_PLAYER};

    if (!maze->getExits().size())
        // No exits were found
        return {NO_EXITS};

    if (nCols * nLines != i)
        // Size in header does not match maze size
        return {INVALID_MAZE_SIZE};

    this->mazeNumber = mazeNumber;
    startTime = std::chrono::steady_clock::now();
    file.close();
    return {};
}

bool Game::isGameOver() const
{
    return exitAt(player->getColumn(), player->getLine()) >= 0 || !player->isAlive();
}

bool Game::isPlayerAlive() const
{
    return player->isAlive();
}

Result Game::movePlayer(int dx, int dy)
{
    int newCol = player->getColumn() + dx;
    int newLine = player->getLine() + dy;

    if (newCol < 0 || newCol >= maze->getNCols() || newLine < 0 || newLine >= maze->getNLines())
        return {OUT_OF_BOUNDS};

    if (nonElectrifiedPostAt(newCol, newLine) >= 0 || deadRobotAt(newCol, newLine) >= 0)
        return {CELL_OCCUPIED};

    if (electrifiedPostAt(newCol, newLine) >= 0)
    {
        player->setAlive(false);
        return {};
    }

    player->setPosition(newCol, newLine);
    return {};
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

void Game::reset()
{
    if (player)
    {
        delete player;
        player = nullptr;
    }
    if (maze)
    {
        delete maze;
        maze = nullptr;
    }
    mazeNumber = "";
    robots = {};
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
