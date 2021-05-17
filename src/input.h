#ifndef INPUT_H
#define INPUT_H
#include "player.h"
#include <string>

class Input
{
public:
	bool getInput(string& input);

private:
	void normalizeInput(string& input);
	string input;
	
};
#endif