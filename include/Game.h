#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Property.h"
#include "Logger.h"

class Game{

    public:
        //Costruttori
        Game();

        //Booleani
        bool isEOG();

        //Functions
        void play();
        void rollDice();
        void move();
        void payFees();

    private:
        Player one_;
        Property prop_;
        Logger log_;
};

#endif