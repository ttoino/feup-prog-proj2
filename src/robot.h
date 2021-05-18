#ifndef ROBOT_H
#define ROBOT_H

class Robot
{
public:
    Robot(size_t column, size_t line);

    void setAlive(bool alive);
    void moveRobot(size_t column, size_t line);

    bool isAlive() const;
    size_t getLine() const;
    size_t getColumn() const;

private:
    bool alive;
    size_t line;
    size_t column;
};

#endif
