#include "Game.h"
#include <iostream>

Game::Game(bool isBotGame){
    players_ = CircularArray<Player>(4);
    no_turns_ = 0;

    if(isBotGame){
        no_max_turns_ = 100;
        players_[0] = Player();
        players_[1] = Player();
        players_[2] = Player();
        players_[3] = Player();
    }else{
        no_max_turns_ = -1;
        players_[0] = Player(false);
        players_[1] = Player();
        players_[2] = Player();
        players_[3] = Player();
    }

    // tabellone assegnato ma non ancora inizializzato
    tabellone_ = CircularArray<Property>(28);

    cell_ids = new std::string[28];
    for(int i = 0; i < 28; i++){
        cell_ids[i] = COORDS.substr(i * 2, 2);
    }

    logger_ = Logger();

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
    for(int i=0; i<24; i++){
        ciotolina.push(ciotolina[i]);
        if((i+1) % 6 == 0) {
            tabellone_.push(Property(' ', 0, 0, 0, 0, 0));
        }
    }
}

bool Game::isEOG(){

    int numPlayers = players_.size();
    int numLosePlayers = 0;

    while (numLosePlayers < numPlayers - 1) {
        numLosePlayers = 0;

        for (int i = 0; i < numPlayers; i++) {
            if (players_[i].getIsLose()) {
                numLosePlayers++;
            }
        }
    }

    return (numLosePlayers == numPlayers - 1);
}

int Game::rollDice(){
    return (rand() % NO_DICE*6) + 1;    
}
void Game::move(){
    
}
void Game::payFees(){

}

void Game::play(){
    std::cout << "Inizio partita" << std::endl;
    std::cout << "Inserisci il nome del giocatore umano: ";
    std::string name;
    std::cin >> name;
    players_[0].setName(name);
    std::cout << "Benvenuto " << players_[0].getName() << std::endl;
    std::cout << "Inserisci il numero di giocatori bot: ";
    int numBot;
    std::cin >> numBot;
    for(int i=1; i<=numBot; i++){
        players_[i].setName("Bot" + std::to_string(i));
        std::cout << "Benvenuto " << players_[i].getName() << std::endl;
    }
    std::cout << "Inserisci il numero di turni massimi: ";
    std::cin >> no_max_turns_;
    std::cout << "Inizio partita" << std::endl;
    
    return;
}