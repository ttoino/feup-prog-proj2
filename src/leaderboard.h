#include <vector>
#include <string>
#include <iostream>

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

struct LeaderboardEntry
{
    /** The player's name */
    std::string name;
    /** The player's points */
    unsigned int points;
};

class Leaderboard
{
public:
    Leaderboard(const std::string &mazeNumber);

    void sort();
    void print(std::ostream &out);
    void save();

private:
    std::vector<LeaderboardEntry> data;
    std::string mazeNumber;

    void load();
};
#endif