// T01_G07

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>
#include "leaderboard.h"
#include "game.h"
#include "util.h"

using namespace std;

/**
 * This enum represents state the game is in.
 */
enum class GameState
{
    /** Game is in the main menu */
    mainMenu,
    /** User is selecting the maze */
    mazeMenu,
    /** User is playing game */
    inGame,
    /** Game has finished and the user is entering their name */
    finished,
    /** User is seeing the leaderboard */
    winners
};

/**
 * Reads the rules from their file and prints them to stdout
 * 
 * @returns A Result object. See its documentation for more info
 */
Result showRules()
{
    ifstream file("RULES.txt");

    // File doesn't exist
    if (!file.is_open())
        return {RULES_NOT_FOUND};

    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }
    cout << '\n';

    return {};
}

/**
 * The start of the game. Asks the user what he wants to do.
 * 
 * @param gameState The game state
 * @param valid The Result object from the last program cycle. Is updated by this function
 * 
 * @returns false if the user wants to exit the game
 */
bool mainMenu(GameState &gameState, Result &valid)
{
    string input;

    // Print menu
    if (valid)
        cout << "Main menu: \n\n"
                "1) Rules \n"
                "2) Play \n"
                "3) Winners \n"
                "0) Exit \n\n";

    cout << "Please insert option: ";

    // Get input
    if (!getInput(input))
        return false; // EOF, exit game

    valid = {};

    if (input == "1")
    {
        // New line for spacing
        cout << "\n";
        valid = showRules(); // Show the rules
    }
    else if (input == "2")
    {
        // New line for spacing
        cout << "\n";
        gameState = GameState::mazeMenu; // Pick the maze
    }
    else if (input == "3")
    {
        // New line for spacing
        cout << "\n";
        gameState = GameState::winners;
    }
    else if (input == "0")
    {
        return false; // Leave the game
    }
    else
    {
        valid = {GENERIC_ERROR};
    }

    return true;
}

/**
 * Checks if a maze number is valid.
 * A number is considered valid if it falls in the range "00" to "99" (needs two characters).
 *
 * @param number The maze number
 * @returns true if the number is valid
 */
bool validMazeNumber(const string &number)
{
    return number.length() == 2 && isdigit(number.at(0)) && isdigit(number.at(1));
}

/**
 * Asks the player for a maze number.
 *
 * @param mazeNumber Where to store the maze number
 * @param valid The Result object from the last program cycle. Is updated by this function
 *
 * @returns false if the user wants to exit the game
 */
bool getMazeNumber(std::string &mazeNumber, Result &valid)
{
    valid = {};

    // Ask user for input
    cout << "Input number of the maze: ";

    // Get input
    if (!getInput(mazeNumber))
        return false;

    // Pad out maze number
    // "" -> "0" -> "00"
    // "5" -> "05"
    while (mazeNumber.length() < 2)
        mazeNumber = "0"s + mazeNumber;

    // Maze number is invalid
    if (!validMazeNumber(mazeNumber))
        valid = {INVALID_MAZE_NUMBER};

    return true;
}

/**
 * Receives input from the player and loads the respective maze.
 *
 * @param gameState The game state
 * @param game The current game
 * @param valid The Result object from the last program cycle. Is updated by this function
 *
 * @returns false if the player wants to exit the game
 */
bool mazeMenu(GameState &gameState, Game &game, Result &valid)
{
    string mazeNumber;
    if (!getMazeNumber(mazeNumber, valid))
        return false;
    if (!valid)
        return true;

    // User wants to return to main menu
    if (mazeNumber == "00")
    {
        cout << "\n";
        gameState = GameState::mainMenu;
        return true;
    }

    valid = game.loadMaze(mazeNumber);

    if (valid)
        // Start the game
        gameState = GameState::inGame;

    return true;
}

/**
 * Asks the player for player movement and moves the player.
 *
 * @param game The current game
 * @param valid The Result object from the last program cycle. Is updated by this function
 *
 * @returns false if the user wants to exit the game
 */
bool movePlayer(Game &game, Result &valid)
{
    string input;

    cout << "Insert movement: ";

    if (!getInput(input))
        return false;

    if (input.length() != 1)
    {
        valid = {GENERIC_ERROR};
        return true;
    }

    char move = tolower(input.at(0));

    switch (move)
    {
    case 'q':
        valid = game.movePlayer(-1, -1);
        return true;
    case 'w':
        valid = game.movePlayer(0, -1);
        return true;
    case 'e':
        valid = game.movePlayer(1, -1);
        return true;
    case 'a':
        valid = game.movePlayer(-1, 0);
        return true;
    case 's':
        valid = game.movePlayer(0, 0);
        return true;
    case 'd':
        valid = game.movePlayer(1, 0);
        return true;
    case 'z':
        valid = game.movePlayer(-1, 1);
        return true;
    case 'x':
        valid = game.movePlayer(0, 1);
        return true;
    case 'c':
        valid = game.movePlayer(1, 1);
        return true;
    default:
        valid = {GENERIC_ERROR};
        return true;
    }
}

/**
 * Handles in game logic: 
 * - Shows the maze 
 * - Asks the player for input and moves them 
 * - Moves the robots 
 * - Handles collisions
 *
 * @param gameState The state the game is in
 * @param game The current game
 * @param valid The Result object from the last program cycle. Is updated by this function
 *
 * @returns false if the user wants to exit the game
 */
bool inGame(GameState &gameState, Game &game, Result &valid)
{
    // Show maze
    if (valid)
        game.displayMaze();

    // Check if game is over
    if (game.isGameOver())
    {
        gameState = GameState::finished;
        return true;
    }

    if (!movePlayer(game, valid))
        return false;

    if (valid)
        game.tick();

    return true;
}

/**
 * Shows the game result.
 * If the player won asks for his name and saves it on the leaderboard.
 *
 * @param gameState The state the game is in
 * @param game The current game
 * @param valid The Result object from the last program cycle. Is updated by this function
 *
 * @returns false if the user wants to exit the game
 */
bool finished(GameState &gameState, Game &game, Result &valid)
{
    if (game.isPlayerAlive())
    {
        if (valid)
            cout << "You win!\n";

        cout << "Please insert your name: ";

        LeaderboardEntry person;

        // Save points as soon as possible
        person.points = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - game.getStartTime()).count();

        if (!getInput(person.name))
            return false;

        // Check name length
        size_t nameLength = utf8Length(person.name);
        if (nameLength > 15)
        {
            valid = {INVALID_NAME};
            return true;
        }
        else if (nameLength == 0)
        {
            valid = {GENERIC_ERROR};
            return true;
        }
        valid = {};
        // Name is valid, pad it out to a length of 15
        person.name += string(15 - nameLength, ' ');
        string mazeNumber = game.getMazeNumber();
        Leaderboard leaderboard(mazeNumber);

        /*if (!searchSameName(leaderboard, person, validInput, errorMessage))
            return false;*/

        LeaderboardEntry *otherPerson = leaderboard.searchSameName(person);
        if (otherPerson)
        {
            cout << "That name already exits in the leaderboard! Do you wish to continue with it? (y/N) ";

            string decision;

            if (!getInput(decision))
                return false;

            if (decision == "y" || decision == "Y")
            {
                // Only save new score if it's better than the current one
                if (person.points < otherPerson->points)
                    otherPerson->points = person.points;
            }
            else
            {
                valid = {ANOTHER_NAME};
                return true;
            }
        }
        else
            leaderboard.addName(person);

        leaderboard.sort();

        cout << '\n';
        leaderboard.print(cout);
        cout << '\n';

        leaderboard.save();
    }
    else
        cout << "You lose :(\n";

    cout << "Press enter to continue\n";
    gameState = GameState::mainMenu;

    string i;
    return getInput(i);
}

/**
 * Asks the player for a maze number and shows its leaderboard.
 *
 * @param gameState The state the game is in
 * @param valid The Result object from the last program cycle. Is updated by this function
 *
 * @returns false if the user wants to exit the game
 */
bool winners(GameState &gameState, Result &valid)
{
    string mazeNumber;

    if (!getMazeNumber(mazeNumber, valid))
        return false;
    if (!valid)
        return true;

    Leaderboard leaderboard(mazeNumber);

    leaderboard.print(cout);
    cout << endl;
    gameState = GameState::mainMenu;

    return true;
}

int main()
{
    /** Whether the program is running */
    bool running = true;
    /** The game state */
    GameState gameState = GameState::mainMenu;
    /** The Result object from the last program cycle */
    Result valid{};
    /** The current game */
    Game game{};

    while (running)
    {
        if (!valid)
            cout << valid << "\n\n";

        switch (gameState)
        {
        case GameState::mainMenu:
            running = mainMenu(gameState, valid);
            break;
        case GameState::mazeMenu:
            running = mazeMenu(gameState, game, valid);
            break;
        case GameState::inGame:
            running = inGame(gameState, game, valid);
            break;
        case GameState::finished:
            running = finished(gameState, game, valid);
            break;
        case GameState::winners:
            running = winners(gameState, valid);
            break;
        }
    }
}