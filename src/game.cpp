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
    unsigned int nLines, nCols;
    file >> nLines >> x >> nCols;

    if (x != 'x' || file.fail())
        return {INVALID_MAZE_HEADER_SIZE};

    maze = new Maze(nLines, nCols);

    char c;
    unsigned int i = 0;
    while (file.get(c))
    {
        switch (c)
        {
        case '\n':
            // Ignore newlines
            continue;
        case ALIVE_ROBOT:
            robots.push_back(Robot(i % nCols, i / nCols));
            break;
        case ALIVE_PLAYER:
            if (player)
                return {MULTIPLE_PLAYERS};

            player = new Player(i % nCols, i / nCols);
            break;
        case EMPTY_CELL:
            // Ignore spaces
            break;
        case ELECTRIFIED_POST:
            maze->getElectrified().push_back(Post(i % nCols, i / nCols));
            break;
        case NON_ELECTRIFIED_POST:
            maze->getNonElectrified().push_back(Post(i % nCols, i / nCols));
            break;
        case EXIT:
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
    const unsigned int newCol = player->getColumn() + dx;
    const unsigned int newLine = player->getLine() + dy;

    if (newCol >= maze->getNCols() || newLine >= maze->getNLines())
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
    std::vector<char> visualMap((size_t)maze->getNCols() * (size_t)maze->getNLines(), EMPTY_CELL);

    for (const Post &post : maze->getElectrified())
        visualMap.at(toIndex(post.getColumn(), post.getLine(), maze->getNCols())) = ELECTRIFIED_POST;

    for (const Post &post : maze->getNonElectrified())
        visualMap.at(toIndex(post.getColumn(), post.getLine(), maze->getNCols())) = NON_ELECTRIFIED_POST;

    for (const Post &exit : maze->getExits())
        visualMap.at(toIndex(exit.getColumn(), exit.getLine(), maze->getNCols())) = EXIT;

    for (const Robot &robot : robots)
        visualMap.at(toIndex(robot.getColumn(), robot.getLine(), maze->getNCols())) = robot.isAlive() ? ALIVE_ROBOT : DEAD_ROBOT;

    visualMap.at(toIndex(player->getColumn(), player->getLine(), maze->getNCols())) = player->isAlive() ? ALIVE_PLAYER : DEAD_PLAYER;

    for (unsigned int i = 0; i < visualMap.size(); ++i)
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

    Robot::resetCounter();
}

void Game::moveRobots()
{
    for (Robot &robot : robots)
    {
        if (!robot.isAlive())
            continue;

        const unsigned int newColumn = robot.getColumn() + sign((long)player->getColumn() - robot.getColumn());
        const unsigned int newLine = robot.getLine() + sign((long)player->getLine() - robot.getLine());

        int i = electrifiedPostAt(newColumn, newLine);
        if (i >= 0)
        {
            robot.setState(RobotState::dead);

            auto electrified = maze->getElectrified();
            Post p = electrified.at(i);
            electrified.erase(electrified.begin() + i);
            maze->getNonElectrified().push_back(p);

            continue;
        }

        i = exitAt(newColumn, newLine);
        if (i >= 0)
            continue;

        i = nonElectrifiedPostAt(newColumn, newLine);
        if (i >= 0)
        {
            robot.setState(RobotState::stuck);
        }

        robot.moveRobot(newColumn, newLine);

        for (Robot &other : robots)
        {
            if (&robot == &other)
                continue;

            if (robotRobotCollision(robot, other))
            {
                robot.setState(RobotState::stuck);
                other.setState(RobotState::stuck);
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

int Game::electrifiedPostAt(const unsigned int column, const unsigned int line) const
{
    auto electrified = maze->getElectrified();
    for (int i = 0; i < electrified.size(); i++)
    {
        auto post = electrified.at(i);

        if (post.getColumn() == column && post.getLine() == line)
            return i;
    }

    return -1;
}

int Game::nonElectrifiedPostAt(const unsigned int column, const unsigned int line) const
{
    auto nonElectrified = maze->getNonElectrified();
    for (int i = 0; i < nonElectrified.size(); i++)
    {
        auto post = nonElectrified.at(i);

        if (post.getColumn() == column && post.getLine() == line)
            return i;
    }

    return -1;
}

int Game::exitAt(const unsigned int column, const unsigned int line) const
{
    auto exits = maze->getExits();
    for (int i = 0; i < exits.size(); i++)
    {
        auto exit = exits.at(i);

        if (exit.getColumn() == column && exit.getLine() == line)
            return i;
    }

    return -1;
}

int Game::deadRobotAt(const unsigned int column, const unsigned int line) const
{
    for (int i = 0; i < robots.size(); i++)
    {
        const auto &robot = robots.at(i);

        if (!robot.isAlive() && robot.getColumn() == column && robot.getLine() == line)
            return i;
    }

    return -1;
}

int Game::aliveRobotAt(const unsigned int column, const unsigned int line) const
{
    for (int i = 0; i < robots.size(); i++)
    {
        const auto &robot = robots.at(i);

        if (robot.isAlive() && robot.getColumn() == column && robot.getLine() == line)
            return i;
    }

    return -1;
}
