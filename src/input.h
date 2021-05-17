#ifndef INPUT_H
#define INPUT_H

#include "player.h"
#include <string>

class Input
{
public:
    bool getInput(std::string &input);

private:
    void normalizeInput(std::string &input);
    std::string input;
};
#endif