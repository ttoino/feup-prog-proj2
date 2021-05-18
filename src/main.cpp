#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>
#include "leaderboard.h"
#include "game.h"

using namespace std;
const string GENERIC_ERROR = "Invalid input!"s;

const string CELL_OCCUPIED = "That cell is occupied!"s;
const string OUT_OF_BOUNDS = "Cannot move out of bounds!"s;

const string INVALID_MAZE_NUMBER = "Must be a number from 1 to 99!"s;
const string MAZE_NOT_FOUND = "That maze could not be found!"s;
const string INVALID_MAZE_HEADER_SIZE = "Invalid maze size in header!"s;
const string INVALID_MAZE_SIZE = "Maze does not match size in header!"s;
const string NO_PLAYER = "Maze has no players!"s;
const string MULTIPLE_PLAYERS = "Maze has multiple players!"s;
const string INVALID_MAZE_CHARACTER = "Invalid character found in maze!"s;

const string INVALID_NAME = "Must have 15 characters or fewer!"s;
const string ANOTHER_NAME = "";

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
    /**User is seing leaderboard*/
    winners,
    /** Game has finished and the user is entering their name */
    finished
};

/**
 * Normalizes input.
 * Replaces all tabs with spaces, removes duplicate spaces and trims spaces from the start and the end.
 *
 * @param input The input to normalize
 */
void normalizeInput(string& input)
{
    char last = 0;
    size_t i = 0;
    while (i < input.length())
    {
        char& c = input.at(i);

        // Replace tabs with spaces
        if (c == '\t')
            c = ' ';

        // Delete character if it is a space at the begining, at the end or after another space
        if (c == ' ' && (last == ' ' || last == 0 || i == input.length() - 1 || i == 0))
        {
            input.erase(i, 1);

            // If we're outside the string, go back one
            if (i == input.length())
                i--;
        }
        else
        {
            i++;
            last = c;
        }
    }
}

/**
 * Gets a line from stdin, normalizes it, and returns false if the eof bit is set.
 *
 * @param input Where to store the input
 * @returns false if the eof bit is set, true otherwise
 */
bool getInput(string& input)
{
    getline(cin, input);
    normalizeInput(input);

    if (cin.eof())
        return false;

    return true;
}

bool showRules()
{
    ifstream file("RULES.TXT");

    // File doesn't exist
    if (!file.is_open())
    {
        //validInput = false;
        //errorMessage = MAZE_NOT_FOUND;
        return false;
    }
    string line;
    while (getline(file, line))
    {
       cout << line << endl;
    }
    return true;
}

bool doPlayerMove(bool& validInput, string& errorMessage, int &dx, int &dy)
{
    string input;

    cout << "Insert movement: ";

    if (!getInput(input))
        return false;

    if (input.length() != 1)
    {
        validInput = false;
        errorMessage = GENERIC_ERROR;
        return true;
    }

    char move = tolower(input.at(0));

    switch (move)
    {
    case 'q':
        dx = -1; dy = -1;
        return true;
    case 'w':
        dx = 0; dy = -1;
        return true;
    case 'e':
        dx = 1; dy = -1;
        return true;
    case 'a':
        dx = -1; dy = 0;
        return true;
    case 's':
        dx = 0; dy = 0;
        return true;
    case 'd':
        dx = 1; dy = 0;
        return true;
    case 'z':
        dx = -1; dy = 1;
        return true;
    case 'x':
        dx = 0; dy = 1;
        return true;
    case 'c':
        dx = 1; dy = 1;
        return true;
    default:
        validInput = false;
        errorMessage = GENERIC_ERROR;
        return true;
    }
}

bool mainMenu(GameState& gameState, bool& validInput, string& errorMessage)
{
    string input;

    // Print menu
    if (validInput)
        cout << "Main menu: \n\n"
        "1) Rules \n"
        "2) Play \n"
        "3) Winners \n"
        "0) Exit \n\n";

    cout << "Please insert option: ";

    // Get input
    if (!getInput(input))
        return false; // EOF, exit game

    validInput = true;

    if (input == "1")
    {
        // New line for spacing
        cout << "\n";
        return showRules(); // Show the rules
    }
    else if (input == "2")
    {
        // New line for spacing
        cout << "\n";
        gameState = GameState::mazeMenu; // Pick the maze
    }
    else if (input == "0")
    {
        return false; // Leave the game
    }
    else if (input == "3")
    {
        gameState = GameState::winners;
        /*Leaderboard winnings;
        winnings.readLeaderboard(mazeNumber);
        winnings.saveLeaderboard(mazeNumber);*/
    }
    else
    {
        validInput = false;
        errorMessage = GENERIC_ERROR;
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
bool validMazeNumber(const string& number)
{
    return number.length() == 2 && isdigit(number.at(0)) && isdigit(number.at(1));
}

bool getmaze(bool& validInput, string& errorMessage, string &mazeNumber)
{
    //// Reset maze variable
    //maze = Maze();
    validInput = true;
    // Ask user for input
    cout << "Input number of the maze: ";

    // Get input
    if (!getInput(mazeNumber))
        return false;

    // Pad out maze number
    // "" -> "0" -> "00"
    // "5" -> "05"
    while (mazeNumber.length() < 2)
    {
        mazeNumber = "0"s + mazeNumber;
    }

    // Maze number is invalid
    if (!validMazeNumber(mazeNumber))
    {
        validInput = false;
        errorMessage = INVALID_MAZE_NUMBER;
        return true;
    }
    return true;
}

/**
 * Receives input from the player and loads the respective maze.
 *
 * @param gameState The game state
 * @param maze Where the maze is stored
 *
 * @returns false if the player wants to exit the game
 */
bool mazeMenu(GameState& gameState, bool& validInput, string& errorMessage, Game &game)
{
    string mazeNumber;
    if (!getmaze(validInput, errorMessage, mazeNumber))
        return false;

    // User wants to return to main menu
    if (mazeNumber == "00")
    {
        cout << "\n";
        gameState = GameState::mainMenu;
        return true;
    }

    if (!game.loadMaze(mazeNumber))
    {
        return true;
    }

    // Start the game
    gameState = GameState::inGame;
    return true;
}

/**
 * Handles in game logic:
 * - Shows the maze
 * - Asks the player for input and moves him
 * - Moves the robots
 * - Handles collisions
 *
 * @param gameState The state the game is in
 * @param maze The maze
 * @param validInput Whether the last input was valid
 * @param errorMessage The error message returned if the input was invalid
 *
 * @returns false if the user wants to exit the game
 */
bool inGame(GameState& gameState, bool& validInput, string& errorMessage, Game &game)
{
    // Show maze
    if (validInput)
    {
        game.displayMaze();
    }

    // Check if game is over
    if (game.isGameOver())
    {
        gameState = GameState::finished;
        return true;
    }
    int dx, dy;
    doPlayerMove(validInput, errorMessage, dx, dy);
    if (!game.movePlayer(dx, dy))
        return false;
    if (!validInput)
        return true;

    game.tick();

    return true;
}

/**
 * Shows the game result.
 * If the player won asks for his name and saves it on the leaderboard.
 *
 * @param gameState The state the game is in
 * @param maze The maze
 * @param validInput Whether the last input was valid
 * @param errorMessage The error message returned if the input was invalid
 *
 * @returns false if the user wants to exit the game
 */
bool finished(GameState& gameState, bool& validInput, string& errorMessage, Game &game)
{
    if (game.isPlayerAlive())
    {
        if (validInput)
            cout << "You win!\n";

        cout << "Please insert your name: ";

        LeaderboardEntry person;
        Leaderboard leaderboard;

        // Save points as soon as possible
        person.points = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - game.getStartTime).count();

        if (!getInput(person.name))
            return false;

        // Check name length
        size_t nameLength = utf8Length(person.name);
        if (nameLength > 15)
        {
            validInput = false;
            errorMessage = INVALID_NAME;
            return true;
        }
        else if (nameLength == 0)
        {
            validInput = false;
            errorMessage = GENERIC_ERROR;
            return true;
        }
        validInput = true;
        // Name is valid, pad it out to a length of 15
        person.name += string(15 - nameLength, ' ');

        
    }
    else
        cout << "You lose :(\n";

    cout << "Press enter to continue\n";
    gameState = GameState::mainMenu;

    string i;
    return getInput(i);
}

bool winner(GameState& gameState, bool& validInput, string& errorMessage, Game& game)
{
    Leaderboard leaderboard;
    string mazeNumber;
    getmaze(validInput, errorMessage, mazeNumber);
    leaderboard.readLeaderboard(mazeNumber);
    leaderboard.saveLeaderboard(mazeNumber);
    return true;

}

int main()
{
    /** Whether the program is running */
    bool running = true;
    /** Whether the last input was valid */
    bool validInput = true;
    /** The message to show if the input was invalid */
    string errorMessage;
    /** The game state */
    GameState gameState = GameState::mainMenu;

    Game game;

    while (running)
    {
        if (!validInput)
            cout << errorMessage << "\n\n";

        switch (gameState)
        {
        case GameState::mainMenu:
            running = mainMenu(gameState, validInput, errorMessage);
            break;
        case GameState::mazeMenu:
            running = mazeMenu(gameState, validInput, errorMessage, game);
            break;
        case GameState::inGame:
            running = inGame(gameState, validInput, errorMessage, game);
            break;
        case GameState::winners:
            running = winner(gameState, validInput, errorMessage, game);
            break;
        case GameState::finished:
            running = finished(gameState, validInput, errorMessage, game);
            break;
        }
    }
}