#include <vector>
#include <string>
#include <iostream>

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

/**
 * This struct represents an entry on the leaderboard.
 */
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
    /**
    * Constructor, initializes the leaderboard by reading it with the function load() and saving the repective maze number
    * 
    * @param mazeNumber Which maze to read (in the range "01" to "99")
    */
    Leaderboard(const std::string &mazeNumber);
    
    /** Sorts a leaderboard by points.*/
    void sort();

    /**
     * Prints a formated leaderboard onto an output stream.
     * @param out Where to print the leaderboard
     */
    void print(std::ostream &out);

    /** Saves a formated leaderboard onto a file */
    void save();

    /**
     * Searches the leaderboard for an entry with the same name.
     *
     * @param person The person with the name to search for
     * @returns the leaderboard entry of the person with the same base on the leaderboard
     */
    LeaderboardEntry* searchSameName(const LeaderboardEntry& person);

    /*
    * Adds another entry to the leaderboard
    * @param person The entry that we want to add
    */
    void addName(LeaderboardEntry& person);

private:

    /**A vector with all the entries inside it*/
    std::vector<LeaderboardEntry> data;

    /**A string with the number of the leaderboard maze*/
    std::string mazeNumber;

    /**Reads a leaderboard file.*/
    void load();
};
#endif