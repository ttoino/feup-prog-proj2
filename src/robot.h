#ifndef PLAYER_H
#define PLAYER_H

class Robot
{
Public:
	Robot(line, collune);
	setAlive(&alive);
	moveRobot(line, collune);
Private:
	bool alive;
	size_t line;
	size_t collune;
};
#endif