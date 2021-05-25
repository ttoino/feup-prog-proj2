// T01_G07

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "leaderboard.h"
#include "util.h"

using namespace std::literals;

Leaderboard::Leaderboard(const std::string &mazeNumber)
    : mazeNumber(mazeNumber)
{
    load();
}

void Leaderboard::load()
{
    std::ifstream file("MAZE_"s + mazeNumber + "_WINNERS.txt"s);

    // File doesn't exist
    if (!file.is_open())
        return;

    // Ignore header
    file.ignore(100, '\n');
    file.ignore(100, '\n');

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream linestream(line);
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
        data.push_back(person);
    }

    file.close();
}

bool compareLeaderboardPoints(LeaderboardEntry person1, LeaderboardEntry person2)
{
    return (person1.points < person2.points);
}

void Leaderboard::sort()
{
    std::sort(data.begin(), data.end(), compareLeaderboardPoints);
}

void Leaderboard::print(std::ostream &out)
{
    if (data.empty())
    {
        out << "Empty list\n";
    }
    else
    {
        out << "Player          - Time\n----------------------\n";

        for (auto person : data)
        {
            out << person.name << " - " << std::setw(4) << std::right << person.points << '\n';
        }
    }
}

void Leaderboard::save()
{
    std::string fileName = "MAZE_"s + mazeNumber + "_WINNERS.txt"s;

    std::ofstream file(fileName);

    print(file);

    file.close();
}

LeaderboardEntry *Leaderboard::searchSameName(const LeaderboardEntry &person)
{
    for (auto &other : data)
    {
        if (other.name == person.name)
        {
            return &other;
        }
    }
    return nullptr;
}

void Leaderboard::addName(LeaderboardEntry &person)
{
    data.push_back(person);
}
