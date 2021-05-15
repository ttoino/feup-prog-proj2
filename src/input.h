#ifndef INPUT_H
#define INPUT_H
#include "player.h"

class Input
{
public:
	bool getInput(string& input);

private:
	void normalizeInput(string& input);
	
};
#endif