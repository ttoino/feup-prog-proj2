#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "leaderboard.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "util.h"
using namespace std;

struct LeaderboardEntry
{
    /** The player's name */
    string name;
    /** The player's points */
    unsigned int points;
};

class Leaderboard {
public:
    void readLeaderboard(const string& mazeNumber);
    void sortLeaderboard();
    void printLeaderboard(ostream& out);
    void saveLeaderboard(const string& mazeNumber);
private:
    vector<LeaderboardEntry> leaderboard;
};
#endif