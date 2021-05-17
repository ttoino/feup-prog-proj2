#ifndef LEADERBOARD_H
#define LEADERBOARD_H

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
   vector<LeaderboardEntry> leaderboard
   bool compareLeaderboardPoints(LeaderboardEntry person1, LeaderboardEntry person2);
};
