#include <cstddef>

#include "player.h"

Player::Player(size_t column, size_t line)
    : column(column), line(line), alive(true)
{
}

void Player::setAlive(bool alive)
{
    this->alive = alive;
}

void Player::setPosition(size_t column, size_t line)
{
    this->column = column;
    this->line = line;
}

bool Player::isAlive() const { return alive; }

size_t Player::getLine() const { return line; }

size_t Player::getColumn() const { return column; }
