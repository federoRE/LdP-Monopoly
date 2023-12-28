#include "Game.h"
#include <iostream>

Game::Game(bool isBotGame){
    no_turns_ = 0;
    no_max_turns_ = (isBotGame ? NO_TURNS_BOT : NO_TURNS_HB);  
    players_ = CircularArray<Player>(NO_PLAYERS);  

    players_.push(Player(isBotGame));
    for(int i=0; i<NO_PLAYERS-1; i++){
        players_.push(Player());
    }

    std::cout << "Ho creato i player" << std::endl;

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
    std::cout << "Ho preparato la ciotolina" << std::endl;
    ciotolina.shuffle();

    tabellone_.push(Property('P', 0, 0, 0, 0, 0));
    ciotolina.shuffle();
    for(int i=0; i<24; i++){
        tabellone_.push(ciotolina[i]);
        if((i+1) % 6 == 0) {
            tabellone_.push(Property(' ', 0, 0, 0, 0, 0));
        }
    }

    std::cout << "Ho preparato il tabellone" << std::endl;

    // Mappa le coordinate
    cell_ids = new std::string[28];
    for(int i = 0; i < 28; i++){
        cell_ids[i] = COORDS.substr(i * 2, 2);
    }
    for(int i = 0; i < 28; i++){
        tabellone_[i].setLegenda(cell_ids[i]);
    }
    std::cout << "Ho mappato le coordinate" << std::endl;
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

void Game::play(){
    while( !isEOG()){
        for(int i = 0; i < 4; i++){
            if(!players_[i].getIsLose()){
                // std::cout << "Turno del giocatore " << players_[i].getName() << std::endl;
                //players_[i].play(tabellone_, cell_ids);
                int dice = rollDice();
                players_[i] += dice;
            }
            std::cout << "ho finito con il giocatore " << players_[i].getName() << std::endl;
        }
        no_turns_++;
    }
    
}