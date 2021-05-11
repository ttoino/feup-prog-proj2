#ifndef PLAYER_H
#define PLAYER_H

class Player
{
Public:
	Player(line, collune);
	setAlive(&alive);
	movePlayer(line, collune);
Private:
	bool alive;
	size_t line;
	size_t collune;
};
#endif