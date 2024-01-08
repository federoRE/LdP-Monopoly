#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Property.h"
#include "CircularArray.h"
#include "Logger.h"

#include <string>
#include <random>
#include <algorithm> // for std::sort
#include <chrono> // for std::chrono::system_clock

static std::random_device dev;
static std::mt19937 rng{dev()};

const int NO_DICE = 2; // numbers of dice
const int NO_PLAYERS = 4; // number of players
const int NO_CELLS = 28; // number of cells
const int NO_TURNS_BOT = 100; // bot-bot turns
const int NO_TURNS_HB = -1; // human-bot turns
// coords string unmapped
const std::string COORDS = "H8H7H6H5H4H3H2H1G1F1E1D1C1B1A1A2A3A4A5A6A7A8B8C8D8E8F8G8";

class Game{

    public:
        /**
         * @brief Construct a new Game object
         * @param isBotGame Booleano che indica se il gioco e' solo bot
        */
        Game(bool isBotGame);

        /**
         * @brief Check if is End Of Game
         * @return true if the game is over
        */
        bool isEOG();

        /**
         * @brief Function to order the players based on dice roll
        */
        void orderPlayers();

        /**
         * @brief Start game loop
        */
        void play();

        

    private:
        // players stored in a special container
        CircularArray<Player> players_{NO_PLAYERS};
        // properties stored in a special container
        CircularArray<Property> tabellone_{NO_CELLS};
        Logger logger_;
        int no_max_turns_; // -1 if human-bot game
        int no_turns_; // number of turns
        bool isBotGame_; // true if bot-bot game

        /**
         * @brief Determine if bot should buy a property
         * @return true if bot should buy a property
        */
        bool randomChance();

        /**
         * @brief Roll the dice
         * @return The sum of the dice
        */
        static int rollDice();

        /**
         * @brief Print the properties of the players
        */
        void printProps();

        /**
         * @brief Print the board
        */
        void printBoard();

        /**
         * @brief Utility function to manage payments
        */
        int payLand(int payer, int pos);

        /**
         * @brief Pay fees to another player
         * @param payer The player who pays
         * @param payee The player who receives the money
         * @param amount The amount of money to pay
        */
        void payFees(int payer, int payee, int pos);

};

#endif