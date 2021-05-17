#include <cstddef>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player(size_t column, size_t line);

    void setAlive(bool alive);
    void setPosition(size_t column, size_t line);

    bool isAlive() const;
    size_t getLine() const;
    size_t getColumn() const;

private:
    bool alive;
    size_t column;
    size_t line;
};
#endif