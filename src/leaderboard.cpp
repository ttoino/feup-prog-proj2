#include "leaderboard.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;


void Leaderboard::readLeaderboard(const string& mazeNumber)
{
    ifstream file("MAZE_"s + mazeNumber + "_WINNERS.txt"s);

    // File doesn't exist
    if (!file.is_open())
        return;

    // Ignore header
    file.ignore(100, '\n');
    file.ignore(100, '\n');

    string line;
    while (getline(file, line))
    {
        stringstream linestream(line);
        LeaderboardEntry person;
        size_t nameLength = 0;
        char c;

        while (nameLength < 15)
        {
            c = linestream.get();
            nameLength += isUtf8Byte1(c);
            person.name += c;
        }

        // Ignore dash
        linestream >> c >> person.points;
        leaderboard.push_back(person);
    }

    file.close();
}

bool Leaderboard::compareLeaderboardPoints(LeaderboardEntry person1, LeaderboardEntry person2)
{
    return (person1.points < person2.points);
}

void Leaderboard::sortLeaderboard()
{
    sort(leaderboard.begin(), leaderboard.end(), compareLeaderboardPoints);
}

void Leaderboard::printLeaderboard(ostream& out)
{
    out << "Player          - Time\n----------------------\n";

    for (auto person : leaderboard)
    {
        out << person.name << " - " << setw(4) << right << person.points << '\n';
    }
}

void Leaderboard::saveLeaderboard(const string& mazeNumber)
{
    string fileName = "MAZE_"s + mazeNumber + "_WINNERS.txt"s;

    ofstream file;
    file.open(fileName);

    printLeaderboard(file, leaderboard);
}
