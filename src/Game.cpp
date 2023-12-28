#include "Game.h"
#include <iostream>

Game::Game(bool isBotGame){
    no_turns_ = 0;
    no_max_turns_ = (isBotGame ? NO_TURNS_BOT : NO_TURNS_HB);  

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

    tabellone_.push(Property('P'));
    for(int i=0; i<24; i++){
        tabellone_.push(ciotolina[i]);
        if((i+1) % 6 == 0) {
            tabellone_.push(Property(' '));
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
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6); 
    int rdn = dist6(rng);
    return rdn;    
}

void Game::move(){
    
}

void Game::payFees(int payer, Player* payee, int amount){
    int newFiorini;
    if (players_[payer].getFiorini() >= amount) {
        newFiorini = players_[payer].getFiorini() - amount;
        players_[payer].setFiorini(newFiorini);
        newFiorini = payee->getFiorini() + amount;
        payee->setFiorini(newFiorini);
    } else {
        players_[payer].setIsLose(true);
    }
}

void Game::orderPlayers(){
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < players_.size() - 1; i++) {
            usleep(10000);
            int dice1 = rollDice();
            int dice2 = rollDice();
            if (dice1 == dice2) {
                sorted = false;
                continue;
            }
            if (dice1 > dice2) {
                players_.swap(i, i + 1);
                players_[i].setRoll(dice2);
                players_[i + 1].setRoll(dice1);
                sorted = false;
            }
        }
    }
}

void Game::play(){
    for(int i=0; i<NO_PLAYERS; i++){
        std::cout << "Il giocatore " << i+1 << 
            " ha tirato i dadi ottenendo un valore di " << 
            players_[i].getRoll() << std::endl;
    }

    while( !isEOG()){
        for(int i = 0; i < 4; i++){
            if(!players_[i].getIsLose()){
                int index_tmp = players_[i].getPos(); //posizione prima del tiro (22)
                players_[i] += rollDice(); //tiro i dadi e aggiorno la posizione (22+8=30 -> 2)
                if(players_[i] < index_tmp){
                    //significa che e' passato dal via
                    players_[i].setFiorini(players_[i].getFiorini() + 20);

                }
                else{
                    //significa che non e' passato dal via
                    std::cout << 
                        "Il giocatore " << players_[i].getName() << 
                        " si trova in " << tabellone_[players_[i].getPos()].getLegenda() << 
                        std::endl;
                }

                if(!players_[i].isBot())
                {

                    //se il giocatore non e' un bot
                    int pos_tmp = players_[i].getPos();
                    std::cout << "Sei in posizione " <<
                        tabellone_[pos_tmp].getLegenda() << ". ";
                    if(tabellone_[pos_tmp].isPropFree())
                    {
                        std::cout << "Owner: " << 
                            (tabellone_[pos_tmp].getOwner() ? 
                            tabellone_[pos_tmp].getOwner()->getName() : "None") << 
                            std::endl;
                        std::cout << "isEdge: " << 
                            (tabellone_[pos_tmp].isEdge() ? "true" : "false") << 
                            std::endl;
                        //se la proprieta' e' libera
                        std::cout << "Il terreno costa: " << 
                        tabellone_[pos_tmp].getLandValue() <<
                        " fiorini(" << tabellone_[players_[i].getPos()].getPropClass() <<
                        "). Vuoi comprarlo?" << std::endl <<
                        "Per comprare scrivi b, per passare scrivi p: ";
                    
                        std::string input= "";
                        std::cin >> input;

                        if(input[0] == 'b')
                        {
                            //compera
                            if(players_[i].getFiorini() >= tabellone_[players_[i].getPos()].getLandValue())
                            {
                                tabellone_[players_[i].getPos()].setOwner(&players_[i]);
                                players_[i].setFiorini(players_[i].getFiorini() - tabellone_[players_[i].getPos()].getLandValue());
                                std::cout << "- Giocatore " << i << 
                                    " ha acquistato il terreno " <<
                                    tabellone_[players_[i].getPos()].getLegenda() <<
                                    std::endl;
                            }
                            else
                            {
                                std::cout << "Non hai abbastanza fiorini" << std::endl;
                            }
                        }
                    }
                    else{
                        //se la proprieta' e' gia' di qualcuno o non e' acquistabile
                        std::cout << "Il terrenon non e' acquistabile" << std::endl;
                    }
                }
            }
        }


        no_turns_++;
    }
    
}