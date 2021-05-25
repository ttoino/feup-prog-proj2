// T01_G07

#include <cstddef>

#include "robot.h"
int Robot::robotCounter = 0;

Robot::Robot(size_t column, size_t line)
{
    this->line = line;
    this->column = column;
    alive = true;
    id = robotCounter;
    robotCounter++;
}

void Robot::setAlive(bool alive)
{
    this->alive = alive;
}

void Robot::moveRobot(size_t column, size_t line)
{
    this->line = line;
    this->column = column;
}

bool Robot::isAlive() const { return alive; }

size_t Robot::getLine() const { return line; }

size_t Robot::getColumn() const { return column; }
