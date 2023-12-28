#ifndef GAME_H
#define GAME_H


/**
 * TODO: capire come gestire la dimensione variabile del 
 *         tabellone (28 caselle) e del numero di giocatori (4)
*/

#include "Player.h"
#include "Property.h"
#include "CircularArray.h"
#include "Logger.h"

#include <string>
#include <random>
#include <unistd.h>

const int NO_DICE = 2;
const int NO_PLAYERS = 4;
const int NO_CELLS = 28;
const int NO_TURNS_BOT = 10;
const int NO_TURNS_HB = -1; // human-bot turns
const std::string COORDS = "H8H7H6H5H4H3H2H1G1F1E1D1C1B1A1A2A3A4A5A6A7A8B8C8D8E8F8G8";

class Game{

    public:
        //Costruttori

        /**
         * @brief Construct a new Game object
         * @param isBotGame Booleano che indica se il gioco e' solo bot
        */
        Game(bool isBotGame);

        //Booleani
        bool isEOG();

        //Functions
        static int rollDice();
        void move();
        void payFees(Player& payer, Player& payee, int amount);
        void orderPlayers();

        void play();

    private:
        CircularArray<Player> players_{NO_PLAYERS};
        CircularArray<Property> tabellone_{NO_CELLS};
        Logger logger_;
        int no_max_turns_; // -1 se non c'e' limite di turni
        int no_turns_;
        std::string *cell_ids;
};

#endif