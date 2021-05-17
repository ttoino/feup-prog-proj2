#include <cstddef>

#include "robot.h"

Robot::Robot(size_t column, size_t line)
    : column(column), line(line), alive(true)
{
}

void Robot::setAlive(bool alive)
{
    this->alive = alive;
}

void Robot::moveRobot(size_t line, size_t column)
{
    this->line = line;
    this->column = column;
}

bool Robot::isAlive() const { return alive; }

size_t Robot::getLine() const { return line; }

size_t Robot::getColumn() const { return column; }