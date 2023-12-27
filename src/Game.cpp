#include "Game.h"
#include <iostream>

Game::Game(bool isBotGame){
    no_turns_ = 0;  
    players_ = CircularArray<Player>(4);  

    
    if(isBotGame){
        no_max_turns_ = 10;
        for(int i = 0; i < 4; i++){
            players_.push(std::move(Player()));
        }
    }else{
        no_max_turns_ = -1;
        players_.push(Player(false));
        players_.push(Player());
        players_.push(Player());
        players_.push(Player());
    }

    players_[0].setName("Fabrizio");
    players_[1].setName("Valentino");
    players_[2].setName("Andrea");
    players_[3].setName("Fresco di zona");
    

    // tabellone assegnato ma non ancora inizializzato
    //logger_ = Logger();

    CircularArray<Property> ciotolina(24);
    // Economic
    for(int i=0; i<8; i++){
        ciotolina.push(Property('E', 6, 3, 3, 2, 4));
    }
    // Standard
    for(int i=0; i<10; i++){
        ciotolina.push(Property('S', 10, 5, 5, 4, 8));
    }
    // Luxury
    const int numIterations = 6;
    for(int i=0; i<numIterations; i++){
        ciotolina.push(Property('L', 20, 10, 10, 7, 14));
    }
    ciotolina.shuffle();

    tabellone_.push(Property('P', 0, 0, 0, 0, 0));
    ciotolina.shuffle();
    for(int i=0; i<24; i++){
        tabellone_.push(ciotolina[i]);
        if((i+1) % 6 == 0) {
            tabellone_.push(Property(' ', 0, 0, 0, 0, 0));
        }
    }

    // Mappa le coordinate
    cell_ids = new std::string[28];
    for(int i = 0; i < 28; i++){
        cell_ids[i] = COORDS.substr(i * 2, 2);
    }
    for(int i = 0; i < 28; i++){
        tabellone_[i].setLegenda(cell_ids[i]);
    }
}

bool Game::isEOG(){

    int numPlayers = players_.size();
    int numLosePlayers = 0;


    for (int i = 0; i < numPlayers; i++) {
        if (players_[i].getIsLose()) {
            numLosePlayers++;
        }
    }

    if(no_max_turns_ == -1){
        return (numLosePlayers == numPlayers - 1);
    }
    else{
        return (numLosePlayers == numPlayers - 1) || (no_turns_ == no_max_turns_);
    }
}

int Game::rollDice(){
    return (rand() % NO_DICE*6) + 1;    
}

void Game::move(){
    
}
void Game::payFees(){

}

void Game::orderPlayers(){
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < players_.size() - 1; i++) {
            int dice1 = rollDice();
            int dice2 = rollDice();
            if (dice1 == dice2) {
                sorted = false;
                continue;
            }
            if (dice1 < dice2) {
                players_.swap(i, i + 1);
                sorted = false;
            }
        }
    }
}

// da qua comincia la traccia del segfault
void Game::play(){
    while( no_turns_ < no_max_turns_){
        for(int i = 0; i < 4; i++){
            if(!players_[i].getIsLose()){
                // std::cout << "Turno del giocatore " << players_[i].getName() << std::endl;
                //players_[i].play(tabellone_, cell_ids);
                int dice = rollDice();
                std::cout << "Il giocatore " << players_[i].getName() << " in posizione " << players_[i].getPos()+1 << std::endl;
                std::cout << "Il giocatore " << players_[i].getName() << " ha fatto " << dice << std::endl;
                players_[i] += dice;
                std::cout << "Il giocatore " << players_[i].getName() << " si trova ora in posizione " << players_[i].getPos()+1 << std::endl;

            }
        }
        no_turns_++;
    }
    
}