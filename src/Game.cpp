#include "Game.h"
#include <iostream>
#include <algorithm>

/**
 * TODO: da rivedere il metodo di pagamento
 * TODO: implementare il logger
 * TODO: implementare la logica di gestione della costruzione
*/

Game::Game(bool isBotGame)
{
    no_turns_ = 0;
    isBotGame_ = isBotGame;
    no_max_turns_ = (isBotGame ? NO_TURNS_BOT : NO_TURNS_HB);  
    logger_ = Logger();

    // giocatori assegnati ma non ancora inizializzati
    players_.push(Player(isBotGame));
    for(int i=0; i<3; i++){
        players_.push(Player(true));
    }

    players_.push(Player(isBotGame));
    players_[0].setName("humano");
    players_[1].setName("Bot1");
    players_[2].setName("Bot2");
    players_[3].setName("Bot3");
    

    // tabellone assegnato ma non ancora inizializzato

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

bool Game::randomChance()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist(0, 3);
    int randomNumber = dist(gen);

    // Ritorna vero al 25%
    return (randomNumber == 0);
}

int Game::rollDice(){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,12); 
    int roll = dist6(rng);
    return roll;
}

void Game::move(){
    
}

/*void Game::payFees(int payer, Player* payee, int amount){
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
        std::cout << "- Il giocatore " << payer+1 << " e' stato eliminato" << std::endl;
    }
}*/

void Game::payFees(int payer, int payee, int pos)
{
    int newFiorini;
    int amount;
    int level;
    std::string log = "";

    level = tabellone_[pos].getLevel();

    if (players_[payer].getFiorini() >= amount) 
    {
        switch (level)
        {
        case 0:
            amount = 0;
            break;
        case 1:
            amount = tabellone_[pos].getHouseRent();
            break;
        case 2:
            amount = tabellone_[pos].getHotelRent();
            break;
        }

        newFiorini = players_[payer].getFiorini() - amount;
        players_[payer].setFiorini(newFiorini);
        newFiorini = players_[payee].getFiorini() + amount;
        players_[payee].setFiorini(newFiorini);
        log = "Giocatore " + std::to_string(payer+1) + " ha pagato " 
            + std::to_string(amount) + " fiorini a giocatore " + std::to_string(payee+1) + " per pernottamento nella casella "
            + tabellone_[pos].getLegenda();
        logger_.addLog(log);
    } 
    else 
    {
        players_[payer].setIsLose(true);
        log = "Giocatore " + std::to_string(payer+1) + " è stato eliminato";
        logger_.addLog(log);
    }
}

int Game::payLand(int payer, int pos){
    int level = tabellone_[pos].getLevel();
    int amount;

    switch (level)
    {
        case 0:
            amount = tabellone_[pos].getHouseValue();
            break;
        case 1:
            amount = tabellone_[pos].getHotelValue();
            break;
    }

    if (players_[payer].getFiorini() >= amount)
    {
        tabellone_[pos].upgrade();
        players_[payer].setFiorini(players_[payer].getFiorini() - amount);
        return tabellone_[pos].getLevel();
    }
    return -1;
}


void Game::orderPlayers() {
    std::cout << "Ordino i giocatori" << std::endl;


    // Inizio, fine, condizione(lambda)
    std::sort(players_.begin(), players_.end(), 
    [](Player& p1, Player& p2) 
    {
        std::cout << "dopo sort 11" << std::endl;
        int d1, d2 = 0;
        do {
            d1 = rollDice();
            d2 = rollDice();
        } while (d1 == d2);
        std::cout << "dopo sort 12" << std::endl;
        
        p1.setRoll(d1 > d2 ? d1 : d2);
        std::cout << "dopo sort 13" << std::endl;
        p2.setRoll(d1 > d2 ? d2 : d1);
        std::cout << "dopo sort 14" << std::endl;

        // SEGFAULT HERE!
        
        return d1 > d2;
    }
    );
    std::cout << "dopo sort 1" << std::endl;

    std::sort(players_.begin(), players_.end(), 
    [](Player& p1, Player& p2) 
    {
        return p1.getRoll() > p2.getRoll();
    }
    );
    std::cout << "dopo sort 2" << std::endl;
}


//TODO: implementeare la sezione player umano
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
                    "- Giocatore " << i+1 << " ha tirato i dadi ottenendo un valore di " <<
                    rd_val << std::endl;
                if(players_[i] < index_tmp){
                    //significa che e' passato dal via
                    players_[i].setFiorini(players_[i].getFiorini() + 20);
                    std::cout << "- Giocatore " << i+1 << 
                            " ha passato dal via e ha ricevuto 20 fiorini" 
                        << std::endl;

                }

                int pos_tmp = players_[i].getPos();
                if(!players_[i].isBot())
                {
                    // INIZIO HUMAN
                    
                    std::cout << "Sei in posizione " <<
                        tabellone_[pos_tmp].getLegenda() << ". ";
                    if(tabellone_[pos_tmp].isPropFree())
                    {
                        // INIZIO PROPRITA' LIBERA
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
                                std::cout << "- Giocatore " << i+1 << //////// LOG
                                    " ha acquistato il terreno " <<
                                    tabellone_[players_[i].getPos()].getLegenda() <<
                                    std::endl;
                            }
                            else
                            {
                                std::cout << "Non hai abbastanza fiorini" << std::endl;
                            }
                        }
                        else if(input == "show") 
                            // 
                            printBoard();

                        // FINE PROPRIETA' LIBERA
                    }
                    else{
                        // INIZIO PROPRIETA' NON LIBERA

                        //se la proprieta' e' gia' di qualcuno o non e' acquistabile
                        std::cout << "Il terreno non e' acquistabile" << std::endl;

                        // FINE PROPRIETA' NON LIBERA
                    }

                    // FINE HUMAN
                }
                else
                {
                    // INIZIO BOT
                    if(tabellone_[pos_tmp].isPropFree()) //Non e' edge e non e' acquistata
                    {
                        //Solo il 25% delle volte
                        if(randomChance())
                        {
                            if(players_[i].getFiorini() >= tabellone_[pos_tmp].getLandValue())
                            {
                                tabellone_[pos_tmp].setOwner(&players_[i]);
                                players_[i].setFiorini(players_[i].getFiorini() - tabellone_[pos_tmp].getLandValue());
                                std::cout << "- Giocatore " << i+1 << //////// LOG
                                    " ha acquistato il terreno " <<
                                    tabellone_[players_[i].getPos()].getLegenda() <<
                                    std::endl;
                            }
                        }
                    }
                    //Se e' lui Owner della casella
                    else if (tabellone_[pos_tmp].getOwner() == &players_[i]){
                        if (tabellone_[pos_tmp].isUpgradeable())
                        {
                            //Solo il 25% delle volte
                            if(randomChance()){
                                int payment = payLand(i, pos_tmp);
                                if (payment != -1)
                                {
                                    std::string log = "";
                                    if (payment == 1)
                                    {
                                        log = "Giocatore " + std::to_string(i+1) + " ha costruito una casa sul terreno " 
                                        + tabellone_[pos_tmp].getLegenda();
                                        logger_.addLog(log);
                                    }
                                    if (payment == 2)
                                    {
                                        log = "Giocatore " + std::to_string(i+1) + " ha migliorato una casa in albergo sul terreno " 
                                        + tabellone_[pos_tmp].getLegenda();
                                        logger_.addLog(log);
                                    }
                                }
                            }
                        } 
                    }

                    else if((tabellone_[pos_tmp].getOwner() != &players_[i]) && 
                            !(tabellone_[pos_tmp].isEdge())){
                            std::cout << "- Giocatore " << i+1 << //////// LOG
                                " ha pagato " << 
                                tabellone_[players_[i].getPos()].getLegenda() <<
                                std::endl;
                            auto owner_id = tabellone_[pos_tmp].getOwner()->getPos();
                            //payFees(i, owner_id, tabellone_[pos_tmp].getLandValue());
                            int j = -1;
                            for (int k = 0; k < NO_PLAYERS; k++){
                                if (players_[k].equals(*tabellone_[pos_tmp].getOwner()))
                                    j = k;
                            }
                            payFees(i, j, pos_tmp);
                    }
                    // FINE BOT
                }
            }
        }


        no_turns_++;
    }
    // FINE GIOCO

    // Stampa il vincitore 
    int playersInGame = 0;
    for(int i = 0; i < NO_PLAYERS; i++)
    {
        if(!players_[i].getIsLose())
        {
            playersInGame++;
        }
    }

    if((playersInGame == 1))
    {
        for(int i = 0; i < NO_PLAYERS; i++)
        {
            if(!players_[i].getIsLose())
            {
                std::string log = "";
                log = "Giocatore " + std::to_string(i+1) + " ha vinto la partita";
                logger_.addLog(log);
            }
        }
    }


    if(playersInGame > 1 && no_turns_ != -1){
        std::vector<int> vincitori;
        int maxFiorini = -1;
        for(int i = 0; i < NO_PLAYERS; i++)
        {
            if (!players_[i].getIsLose() && players_[i].getFiorini() >= maxFiorini) 
            {
                if (players_[i].getFiorini() > maxFiorini) 
                {
                    vincitori.clear();
                    maxFiorini = players_[i].getFiorini();
                }
                vincitori.push_back(i);
            }
        }
        std::string log = "";
        if (vincitori.size() == 1){
            log = "Giocatore " + std::to_string(vincitori[0] + 1) + " ha vinto la partita";
            logger_.addLog(log);
        }
        else{
            log += "I giocatori ";
            for (int winner : vincitori) {
                log += std::to_string(winner + 1) + " ";
            }
            log += "hanno vinto in ex-equo";
            logger_.addLog(log);
        }
    }
    logger_.saveFile();
}


// TODO: inserire info secondarie, come player,case,hotel 
void Game::printBoard(){
    std::cout << "" <<
        "\t" << " 1" << "\t" << " 2" << "\t" << " 3" << "\t" << " 4" << "\t" << " 5" << "\t" << " 6" << "\t" << " 7" << "\t" << " 8" << "\t" <<
    std::endl;
    std::cout << "--------------------------------------------------------------------------------"
    << std::endl;
    std::cout << "A" << 
        "\t" << "|" << tabellone_[14].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[15].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[16].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[17].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[18].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[19].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[20].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[21].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "B" <<
        "\t" << "|" << tabellone_[13].getPropClass() << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone_[22].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "C" <<
        "\t" << "|" << tabellone_[12].getPropClass() << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone_[23].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "D" <<
        "\t" << "|" << tabellone_[11].getPropClass() << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone_[24].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "E" <<
        "\t" << "|" << tabellone_[10].getPropClass() << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone_[25].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "F" <<
        "\t" << "|" << tabellone_[9].getPropClass() << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone_[26].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "G" <<
        "\t" << "|" << tabellone_[8].getPropClass() << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone_[27].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "H" << 
        "\t" << "|" << tabellone_[7].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[6].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[5].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[4].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[3].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[2].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[1].getPropClass() << "|" << "\t" <<
        "|" << tabellone_[0].getPropClass() << "|" << "\t" <<
    std::endl;
}
