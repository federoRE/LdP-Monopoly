#include "Game.h"
#include <iostream>

/**
 * TODO: da rivedere il metodo di pagamento
 * TODO: implementare il logger
 * TODO: implementare la logica di gestione della costruzione
*/

Game::Game(bool isBotGame){
    no_turns_ = 0;
    no_max_turns_ = (isBotGame ? NO_TURNS_BOT : NO_TURNS_HB);  

    players_.push(Player(isBotGame));
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
    if (players_[payer].getFiorini() >= amount) 
    {
        newFiorini = players_[payer].getFiorini() - amount;
        players_[payer].setFiorini(newFiorini);
        newFiorini = payee->getFiorini() + amount;
        payee->setFiorini(newFiorini);
    } 
    else 
    {
        players_[payer].setIsLose(true);
    }
}

void Game::payFees(int payer, int payee, int amount)
{
    int newFiorini;
    if (players_[payer].getFiorini() >= amount) 
    {
        newFiorini = players_[payer].getFiorini() - amount;
        players_[payer].setFiorini(newFiorini);
        newFiorini = players_[payee].getFiorini() + amount;
        players_[payee].setFiorini(newFiorini);
    } 
    else 
    {
        players_[payer].setIsLose(true);
    }
}


void Game::orderPlayers(){
    for(int i = 0; i < NO_PLAYERS - 1; i++){
        for(int j = 0; j < NO_PLAYERS - i - 1; j++){
            int d1, d2 = 0;
            d1 = rollDice();
            d2 = rollDice();

            while(d1 == d2){
                d1 = rollDice();
                usleep(500000);
                d2 = rollDice();
            }
            players_[j].setRoll(d1);
            players_[j+1].setRoll(d2);
            if(players_[j].getRoll() < players_[j+1].getRoll()){
                // Swap players
                Player temp = players_[j];
                players_[j] = players_[j+1];
                players_[j+1] = temp;
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

    for(int i=3; i>0; i--){
        std::cout << "Inizio il gioco in " << i << std::endl;
        usleep(1000000);
    }

    while( !isEOG()){
        for(int i = 0; i < 4; i++){
            if(!players_[i].getIsLose()){

                /**
                 * Se il giocatore attuale non ha perso, allora gioca
                 * le mosse. Qui si entra indipendentemente dal fatto
                 * che sia un bot o meno.
                */

                int index_tmp = players_[i].getPos(); //posizione prima del tiro (22)
                int rd_val = rollDice(); 
                players_[i] += rd_val; //tiro i dadi e aggiorno la posizione (22+8=30 -> 2)
                std::cout <<  //////// LOG
                    "- Giocatore " << i << " ha tirato i dadi ottenendo un valore di " <<
                    rd_val << std::endl;
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

                int pos_tmp = players_[i].getPos();
                if(!players_[i].isBot())
                {
                    // INIZIO HUMAN
                    
                    std::cout << "Sei in posizione " <<
                        tabellone_[pos_tmp].getLegenda() << ". ";
                    if(tabellone_[pos_tmp].isPropFree())
                    {
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
                            if(players_[i].getFiorini() >= tabellone_[pos_tmp].getLandValue())
                            {
                                tabellone_[pos_tmp].setOwner(&players_[i]);
                                players_[i].setFiorini(players_[i].getFiorini() - tabellone_[pos_tmp].getLandValue());
                                std::cout << "- Giocatore " << i << //////// LOG
                                    " ha acquistato il terreno " <<
                                    tabellone_[players_[i].getPos()].getLegenda() <<
                                    std::endl;
                                std::cout << "Giocatore " << i << 
                                    " ha " << players_[i].getFiorini() << 
                                    " fiorini" << std::endl;
                            }
                            else
                            {
                                std::cout << "Non hai abbastanza fiorini" << std::endl;
                            }
                        }
                    }
                    else{
                        //se la proprieta' e' gia' di qualcuno o non e' acquistabile
                        std::cout << "Il terreno non e' acquistabile" << std::endl;
                    }

                    // FINE HUMAN
                }
                else
                {
                    // INIZIO BOT
                    if(tabellone_[pos_tmp].isPropFree())
                    {
                        if(players_[i].getFiorini() >= tabellone_[pos_tmp].getLandValue())
                        {
                            std::cout << "[BOT] Coppo il terreno " << 
                            tabellone_[pos_tmp].getLegenda() << 
                            std::endl;
                            tabellone_[pos_tmp].setOwner(&players_[i]);
                            players_[i].setFiorini(players_[i].getFiorini() - tabellone_[pos_tmp].getLandValue());
                            std::cout << "- Giocatore " << i << //////// LOG
                                " ha acquistato il terreno " <<
                                tabellone_[players_[i].getPos()].getLegenda() <<
                                std::endl;
                        }
                        
                    }
                    else if(
                        (tabellone_[pos_tmp].getOwner() != &players_[i]) && 
                            !(tabellone_[pos_tmp].isEdge())
                        )
                    {
                        std::cout << "[BOT] Pago il terreno " << 
                        tabellone_[pos_tmp].getLegenda() << 
                        std::endl;
                        std::cout << "- Giocatore " << i << //////// LOG
                            " ha pagato " << 
                            tabellone_[players_[i].getPos()].getLegenda() <<
                            std::endl;
                        auto owner_id = tabellone_[pos_tmp].getOwner()->getPos();
                        payFees(i, owner_id, tabellone_[pos_tmp].getLandValue());
                        //payFees(i, tabellone_[pos_tmp].getOwner(), tabellone_[pos_tmp].getLandValue());
                    }

                    // FINE BOT
                }
            }
        }


        no_turns_++;
    }
    
}