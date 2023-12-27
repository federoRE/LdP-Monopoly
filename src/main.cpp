#include <iostream>
#include <string>
#include "Game.h"

int main(void){
    Game game = Game(true);
    game.orderPlayers();
    game.play();

    std::cout << "Game over" << std::endl;

    //il segfault viene riportato qui, dopo la fine del gioco
    // mancanza distruttore??
    return 0; 
}