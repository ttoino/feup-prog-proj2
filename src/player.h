#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(line, collune);
	setAlive(&alive);
	movePlayer(line, collune);
private:
	bool alive;
	size_t line;
	size_t collune;
};
#endif