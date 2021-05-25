// T01_G07

#ifndef ROBOT_H
#define ROBOT_H

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
    Robot(size_t column, size_t line);

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
    void moveRobot(size_t column, size_t line);

    /** @returns Whether the robot is alive or dead */
    bool isAlive() const;

    /** @returns The position on the y-axis */
    size_t getLine() const;

    /** @returns The position on the x-axis */
    size_t getColumn() const;

private:
    /**used to attribute automatically the id to the robots*/
    static int robotCounter;
    /**differentiates the different robots by giving them an id*/
    int id;
    /** Whether the robot is alive or dead */
    bool alive;
    /** Position on the y-axis */
    size_t line;
    /** Position on the x-axis */
    size_t column;
};

#endif
