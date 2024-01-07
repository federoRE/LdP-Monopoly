#include <iostream>
#include <string>
#include "Game.h"

// TODO: implementare il parsing degli argomenti
// main human
// main computer
int main(int argc, char** argv)
{

    bool isBotGame = false;

    if (argc != 2)
    {
        std::cout << 
            "Errore: numero di argomenti non valido."
            << std::endl;
        return 1;
    }
    else
    {
        std::string arg = argv[1];
        if (arg != "human" && arg != "computer")
        {
            std::cout << 
                "Errore: argomento non valido."
                << std::endl;
            return 1;
        }
        else{
            if(arg == "human")
            {
                std::cout << 
                    "Hai scelto di giocare contro i computer."
                    << std::endl;
                isBotGame = false;
            }
            else
            {
                std::cout << 
                    "Hai scelto una partita tra computer."
                    << std::endl;
                isBotGame = true;
            }
        }
    
    }


    std::cout << 
        "Benvenuto. Sto preparando il gioco."
        << std::endl;
    Game game = Game(isBotGame);

    game.orderPlayers();
    game.play();

    return 0; 
}