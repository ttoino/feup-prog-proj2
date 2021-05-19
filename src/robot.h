#ifndef ROBOT_H
#define ROBOT_H

class Robot
{
public:
    /** Constructer, initializes de Robot with their position
    * @param column The column of the robot position
    * @param line The line of the robot position
    */
    Robot(size_t column, size_t line);

    /**
    * Change the state of the robot to false if the robot is dead 
    * @param alive Boolian expression
    */
    void setAlive(bool alive);

    /**
     * Uptade the position of the robot to the one after the player movement
     * @param column Number of the new collun
     * @param line Number of the new line
     */
    void moveRobot(size_t column, size_t line);

    /**
    * checks if the robot is alive or dead
    * @return true if the robot is alive, false if the robot is stuck or dead
    */
    bool isAlive() const;

    /** @return returns the line of the robot position at the moment*/
    size_t getLine() const;

    /** @return returns the column of the position at the moment*/
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
