// T01_G07

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <vector>
#include <string>
#include <iostream>

/**
 * This struct represents an entry on the leaderboard.
 */
struct LeaderboardEntry
{
    /** The player's name */
    std::string name;
    /** The player's points */
    unsigned long long points = 0;
};

class Leaderboard
{
public:
    /**
    * Constructor, initializes the leaderboard by reading it with the function load() and saving the respective maze number
    * 
    * @param mazeNumber Which maze to read (in the range "01" to "99")
    */
    Leaderboard(const std::string &mazeNumber);

    /** Sorts the leaderboard by points */
    void sort();

    /**
     * Prints the formated leaderboard onto an output stream
     * 
     * @param out Where to print the leaderboard
     */
    void print(std::ostream &out);

    /** Saves the formated leaderboard onto its file */
    void save();

    /**
     * Searches the leaderboard for an entry with the same name
     *
     * @param person The person with the name to search for
     * 
     * @returns a pointer to the leaderboard entry of the person with the same name on the leaderboard
     */
    LeaderboardEntry *searchSameName(const LeaderboardEntry &person);

    /**
    * Adds an entry to the leaderboard
    * 
    * @param person The entry to add
    */
    void addName(LeaderboardEntry &person);

private:
    /** A vector holding the entries */
    std::vector<LeaderboardEntry> data;

    /** The number of the maze */
    std::string mazeNumber;

    /** Loads the leaderboard from its file */
    void load();
};
#endif