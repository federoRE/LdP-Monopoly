#include <iostream>
#include <string>
#include "Game.h"

int main(void){
    std::cout << 
        "Benvenuto. Sto preparando il gioco."
        << std::endl;
    Game game = Game(true);

    game.orderPlayers();
    game.play();

    return 0; 
}