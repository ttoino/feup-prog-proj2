// T01_G07

#ifndef ROBOT_H
#define ROBOT_H

#include <cstddef>

/**
 * This class represents a robot
 */
class Robot
{
public:
    /** 
     * Creates an alive robot with the specified position
     * 
     * @param column The position on the x-axis
     * @param line The position on the y-axis
     */
    Robot(unsigned int column, unsigned int line);

    /**
     * Update the robot to be alive or dead
     * 
     * @param alive Whether the robot is alive or dead
     */
    void setAlive(bool alive);

    /**
     * Updates the robot's position
     * 
     * @param column The position on the x-axis
     * @param line The position on the y-axis
     */
    void moveRobot(unsigned int column, unsigned int line);

    /** @returns Whether the robot is alive or dead */
    bool isAlive() const;

    /** @returns The position on the y-axis */
    unsigned int getLine() const;

    /** @returns The position on the x-axis */
    unsigned int getColumn() const;

private:
    /**used to attribute automatically the id to the robots*/
    static int robotCounter;
    /**differentiates the different robots by giving them an id*/
    int id;
    /** Whether the robot is alive or dead */
    bool alive;
    /** Position on the y-axis */
    unsigned int line;
    /** Position on the x-axis */
    unsigned int column;
};

#endif
