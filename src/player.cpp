// T01_G07

#include <cstddef>

#include "player.h"

Player::Player(unsigned int column, unsigned int line)
    : column(column), line(line), alive(true) {}

void Player::setAlive(bool alive)
{
    this->alive = alive;
}

void Player::setPosition(unsigned int column, unsigned int line)
{
    this->column = column;
    this->line = line;
}

bool Player::isAlive() const { return alive; }

unsigned int Player::getLine() const { return line; }

unsigned int Player::getColumn() const { return column; }
