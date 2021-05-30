// T01_G07

#include "robot.h"

int Robot::robotCounter = 0;

void Robot::resetCounter()
{
    robotCounter = 0;
}

Robot::Robot(unsigned int column, unsigned int line)
    : line(line), column(column), state(RobotState::alive), id(++robotCounter) {}

void Robot::setState(RobotState state)
{
    this->state = state;
}

void Robot::moveRobot(unsigned int column, unsigned int line)
{
    this->line = line;
    this->column = column;
}

bool Robot::isAlive() const { return state == RobotState::alive; }

unsigned int Robot::getLine() const { return line; }

unsigned int Robot::getColumn() const { return column; }
