// T01_G07

#ifndef ROBOT_H
#define ROBOT_H

/**  
 * This enum represents the state the robot is in
 */
enum class RobotState
{
    /** The robot is alive */
    alive,
    /** The robot has hit an electrified post and is dead */
    dead,
    /** The robot has it a post or another robot and is stuck */
    stuck
};

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
    void setState(RobotState state);

    /**
     * Updates the robot's position
     * 
     * @param column The position on the x-axis
     * @param line The position on the y-axis
     */
    void moveRobot(unsigned int column, unsigned int line);

    /** @returns Whether the robot is alive */
    bool isAlive() const;

    /** @returns The position on the y-axis */
    unsigned int getLine() const;

    /** @returns The position on the x-axis */
    unsigned int getColumn() const;

    /** Resets robot counter to 0 */
    static void resetCounter();

private:
    /** Used to automatically attribute an id to a robot */
    static int robotCounter;
    /** Used to identify different robots */
    int id;
    /** Whether the robot is alive or dead */
    RobotState state;
    /** Position on the y-axis */
    unsigned int line;
    /** Position on the x-axis */
    unsigned int column;
};

#endif
