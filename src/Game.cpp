/**
 * @author Federico Borsati
 * @author JFK
*/

#include "Game.h"
#include <iostream>


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
    players_[0].setName("tizio");
    players_[1].setName("caio");
    players_[2].setName("sempronio");
    players_[3].setName("fabrizio");
    

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
    ciotolina.shuffle();

    tabellone_.push(Property('P'));
    for(int i=0; i<24; i++){
        tabellone_.push(ciotolina[i]);
        if((i+1) % 6 == 0) {
            tabellone_.push(Property(' '));
        }
    }

    // Mappa le coordinate
    std::string* cell_ids = new std::string[28];
    for(int i = 0; i < 28; i++){
        cell_ids[i] = COORDS.substr(i * 2, 2);
    }
    for(int i = 0; i < 28; i++){
        tabellone_[i].setLegenda(cell_ids[i]);
    }
    
    std::cout << "Ho preparato il tabellone" << std::endl;
}


bool Game::isEOG(){

    int numPlayers = players_.size(); //4
    int numLosePlayers = 0; //3


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


void Game::orderPlayers() {
    std::cout << "Ordino i giocatori" << std::endl;
    std::vector <int> rolls;
    // std::set<int> rolls; // Use a set to store unique rolls

    for(int i=0; i<NO_PLAYERS; i++){
        int roll = 0;
        bool isok = true;
        do{
            roll = rollDice();
            isok = std::find(rolls.begin(), rolls.end(), roll) == rolls.end();
        }
        while(!isok && i<NO_PLAYERS);
        rolls.push_back(roll); // Insert the unique roll into the set
    }

    int index = 0;
    for (const auto& roll : rolls) {
        players_[index].setRoll(roll);
        index++;
    }

    for (int i = 0; i < NO_PLAYERS - 1; i++) {
        for (int j = 0; j < NO_PLAYERS - i - 1; j++) {
            if (players_[j].getRoll() < players_[j + 1].getRoll()) {
                // Swap players
                players_.swap(j, j + 1);
            }
        }
    }

    for(int i=0; i<NO_PLAYERS; i++){
        players_[i].setId(i+1);
    }
}


void Game::play(){
    for(int i=0; i<NO_PLAYERS; i++){
        std::string log = "";
        log = "Giocatore " + std::to_string(i+1) + 
            " ha tirato i dadi ottenendo un valore di " + 
            std::to_string(players_[i].getRoll());
        logger_.addLog(log);
    }

    if(!isBotGame_)
    {
        int idHuman = 0;
        int id_vec_h = 0;
        for(int i=0; i<NO_PLAYERS; i++)
        {
            if(!players_[i].isBot())
            {
                idHuman = players_[i].getId();
                id_vec_h = i;
            }
        }
        std::cout << "Il giocatore " << idHuman << " e' l'umano. La posizione di partenza e' " << id_vec_h+1 << std::endl;
    }

    for(int i=3; i>0; i--){
        std::cout << "Inizio il gioco in " << i << std::endl;
        usleep(1000000);
    }

    while(!isEOG()){
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
                std::string log = "";
                log = "Giocatore " + std::to_string(players_[i].getId()) + 
                    " ha tirato i dadi ottenendo un valore di " + 
                    std::to_string(rd_val);
                logger_.addLog(log);
                log = "Giocatore " + std::to_string(players_[i].getId()) + 
                    " è arrivato alla casella " + tabellone_[players_[i].getPos()].getLegenda();
                logger_.addLog(log);
                if(players_[i] < index_tmp){
                    //significa che e' passato dal via
                    players_[i].setFiorini(players_[i].getFiorini() + 20);
                    std::string log = "";
                    log = "Giocatore " + std::to_string(players_[i].getId()) + 
                            " è passato dal via e ha ritirato 20 fiorini";
                    logger_.addLog(log);
                }

                int pos_tmp = players_[i].getPos();
                if(!players_[i].isBot())
                {
                    // INIZIO HUMAN
                    
                    std::cout << "Sei in posizione " <<
                        tabellone_[pos_tmp].getLegenda() << ". ";
                    if(tabellone_[pos_tmp].isPropFree())
                    {
                        // INIZIO PROPRIETA' LIBERA
                        std::cout << "Il terreno costa: " << 
                        tabellone_[pos_tmp].getLandValue() <<
                        " fiorini(" << tabellone_[players_[i].getPos()].getPropClass() <<
                        ")." << std::endl;

                        std::cout <<
                            "[GAME] Lista comandi: " << std::endl <<
                            " - S: compra il terreno" << std::endl <<
                            " - N: passa il turno" << std::endl <<
                            " - show: mostra il tabellone" << std::endl <<
                            " - prop: mostra le caselle possedute dai giocatori" <<
                        std::endl;
                        std::string input= "";
                        bool isAlredyBought = false;
                        do{
                            std::cout << "Inserisci comando: ";
                            std::cin >> input;
                            if((input[0] == 'S' || input[0] == 's') && input.length() == 1)
                            {
                                if(isAlredyBought)
                                {
                                    std::cout << "Hai gia' acquistato il terreno" << std::endl;
                                    continue;
                                }
                                else
                                {
                                    isAlredyBought = true;
                                    //compera
                                    if(players_[i].getFiorini() >= tabellone_[pos_tmp].getLandValue())
                                    {
                                        tabellone_[pos_tmp].setOwner(&players_[i]);
                                        players_[i].setFiorini(players_[i].getFiorini() - tabellone_[pos_tmp].getLandValue());
                                        log = "Giocatore " + std::to_string(players_[i].getId()) +
                                            " ha acquistato il terreno " +
                                            tabellone_[players_[i].getPos()].getLegenda();
                                        logger_.addLog(log);
                                    }
                                    else
                                    {
                                        std::cout << "Non hai abbastanza fiorini" << std::endl;
                                    }
                                }
                            }
                            else if(input == "show") 
                            {
                                printBoard();
                                printProps();
                                std::cout << "Fiorini" << std::endl;
                                for(int i=0; i<NO_PLAYERS; i++)
                                {
                                    std::cout << "\tGiocatore " << players_[i].getId() << ": " << players_[i].getFiorini() << std::endl;
                                }
                            }
                            else if(input == "gscotty")
                            {
                                std::cout << "Hai attivato la modalita' God Scotty" << std::endl;
                                players_[i].setFiorini(players_[i].getFiorini() + 1000);
                                for(int i=0;i<28;i++){
                                    if(!tabellone_[i].isEdge())
                                    {
                                        tabellone_[i].setOwner(&players_[0]);
                                        tabellone_[i].upgrade();
                                        tabellone_[i].upgrade();
                                    }
                                }
                                printBoard();
                            }
                            else if(input == "help")
                            {
                                std::cout <<
                                    "[GAME] Lista comandi: " << std::endl <<
                                    (isAlredyBought ? "" : " - S: compra il terreno") << std::endl <<
                                    " - N: passa il turno" << std::endl <<
                                    " - show: mostra il tabellone" << std::endl <<
                                    " - prop: mostra le caselle possedute dai giocatori" <<
                                std::endl;
                            }
                            else if(input == "prop")
                            {
                                printProps();
                            }
                            else
                            {
                                std::cout << "Comando non riconosciuto" << std::endl;
                            }
                        }
                        while(input != "end" && input != "N" && input != "n");


                        // FINE PROPRIETA' LIBERA
                    }
                    else{
                        // INIZIO PROPRIETA' NON LIBERA

                        //se la proprieta' e' gia' di qualcuno o non e' acquistabile
                        if(tabellone_[pos_tmp].getOwner() == &players_[i])
                        {
                            //se e' gia' di lui
                            if(tabellone_[pos_tmp].isUpgradeable())
                            {
                                //se e' migliorabile
                                std::cout << "Il terreno e' migliorabile" << std::endl;
                                std::cout << "Il terreno costa: " << 
                                tabellone_[pos_tmp].getHouseValue() <<
                                " fiorini(" << tabellone_[players_[i].getPos()].getPropClass() <<
                                ")." << std::endl;

                                std::cout <<
                                    "[GAME] Lista comandi: " << std::endl <<
                                    " - S: upgrade casella" << std::endl <<
                                    " - N: passa il turno" << std::endl <<
                                    " - show: mostra il tabellone" << std::endl <<
                                    " - prop: mostra le caselle possedute dai giocatori" << std::endl <<
                                std::endl;
                                std::string input= "";
                                bool isAlredyBought = false;
                                do{
                                    std::cout << "Inserisci comando: ";
                                    std::cin >> input;
                                    if((input == "S" || input == "s") && input.length() == 1)
                                    {
                                        if(isAlredyBought)
                                        {
                                            std::cout << "Hai gia' migliorato il terreno" << std::endl;
                                            continue;
                                        }
                                        else
                                        {
                                            isAlredyBought = true;
                                            //compera
                                            if(players_[i].getFiorini() >= tabellone_[pos_tmp].getHouseValue())
                                            {
                                                int payment = payLand(i, pos_tmp);
                                                if (payment != -1)
                                                {
                                                    std::string log = "";
                                                    if (payment == 1)
                                                    {
                                                        log = "Giocatore " + std::to_string(players_[i].getId()) + " ha costruito una casa sul terreno " 
                                                        + tabellone_[pos_tmp].getLegenda();
                                                        logger_.addLog(log);
                                                    }
                                                    if (payment == 2)
                                                    {
                                                        log = "Giocatore " + std::to_string(players_[i].getId()) + " ha migliorato una casa in albergo sul terreno " 
                                                        + tabellone_[pos_tmp].getLegenda();
                                                        logger_.addLog(log);
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                std::cout << "Non hai abbastanza fiorini" << std::endl;
                                            }
                                        }
                                    }
                                    else if(input == "show") 
                                    {
                                        printBoard();
                                        printProps();
                                        std::cout << "Fiorini" << std::endl;
                                        for(int i=0; i<NO_PLAYERS; i++)
                                        {
                                            std::cout << "\tGiocatore " << players_[i].getId() << ": " << players_[i].getFiorini() << std::endl;
                                        }
                                    }
                                    else if(input == "gscotty")
                                    {
                                        std::cout << "Hai attivato la modalita' God Scotty" << std::endl;
                                        players_[i].setFiorini(players_[i].getFiorini() + 1000);
                                        for(int i=0;i<28;i++){
                                            if(!tabellone_[i].isEdge())
                                            {
                                                tabellone_[i].setOwner(&players_[0]);
                                                tabellone_[i].upgrade();
                                                tabellone_[i].upgrade();
                                            }
                                        }
                                        printBoard();
                                    }
                                    else if(input == "help")
                                    {
                                        std::cout <<
                                            "[GAME] Lista comandi: " << std::endl <<
                                            (isAlredyBought ? "" : " - S: upgrade casella") << std::endl <<
                                            " - N: passa il turno" << std::endl <<
                                            " - show: mostra il tabellone" << std::endl <<
                                            " - prop: mostra le caselle possedute dai giocatori" <<
                                        std::endl;
                                    }
                                    else if(input == "prop")
                                    {
                                        printProps();
                                    }
                                    else if(input == "help") 
                                    {
                                        std::cout <<
                                            "[GAME] Lista comandi: " << std::endl <<
                                            (isAlredyBought ? "" : " - S: upgrade casella") << std::endl <<
                                            " - N: passa il turno" << std::endl <<
                                            " - show: mostra il tabellone" << std::endl <<
                                            " - prop: mostra le caselle possedute dai giocatori" << 
                                        std::endl;
                                    }
                                    else
                                    {
                                        std::cout << "Comando non riconosciuto" << std::endl;
                                    }
                                }
                                while(input != "end" && input != "N" && input != "n");
                            }
                            else
                            {
                                std::cout << "Il terreno non e' migliorabile" << std::endl;
                            }
                        }
                        else
                        {
                            // se non e' di lui
                            if(!tabellone_[pos_tmp].isEdge())
                            {
                                int owner_id = tabellone_[pos_tmp].getOwner()->getPos();
                                //payFees(i, owner_id, tabellone_[pos_tmp].getLandValue());
                                int j = -1;
                                for (int k = 0; k < NO_PLAYERS; k++){
                                    if (players_[k].equals(*tabellone_[pos_tmp].getOwner()))
                                        j = k;
                                }
                                payFees(i, j, pos_tmp);
                            }
                            else
                            {
                                std::cout << "Il terreno non e' acquistabile" << std::endl;
                            }
                        }
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
                                log = "Giocatore " + std::to_string(i+1) +
                                            " ha acquistato il terreno " +
                                            tabellone_[players_[i].getPos()].getLegenda();
                                        logger_.addLog(log);
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
                                        log = "Giocatore " + std::to_string(players_[i].getId()) + " ha costruito una casa sul terreno " 
                                        + tabellone_[pos_tmp].getLegenda();
                                        logger_.addLog(log);
                                    }
                                    if (payment == 2)
                                    {
                                        log = "Giocatore " + std::to_string(players_[i].getId()) + " ha migliorato una casa in albergo sul terreno " 
                                        + tabellone_[pos_tmp].getLegenda();
                                        logger_.addLog(log);
                                    }
                                }
                            }
                        } 
                    }

                    else if((tabellone_[pos_tmp].getOwner() != &players_[i]) && 
                            !(tabellone_[pos_tmp].isEdge())){
                            int owner_id = tabellone_[pos_tmp].getOwner()->getPos();
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
            std::string log = "";
            log = "Giocatore " + std::to_string(players_[i].getId()) +
                " ha finito il turno";
            logger_.addLog(log);
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
                log = "Giocatore " + std::to_string(players_[i].getId()) + " ha vinto la partita";
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
            log = "I giocatori ";
            for (int winner : vincitori) {
                log += std::to_string(winner + 1) + " ";
            }
            log += "hanno vinto in ex-equo";
            logger_.addLog(log);
        }
    }
    logger_.saveFile();
}


bool Game::randomChance()
{
    static std::uniform_int_distribution<int> dist(0, 3);
    int randomNumber = dist(rng);

    // Ritorna vero al 25%
    return (randomNumber == 0);
}

void Game::remOwner(Player *player)
{
    for(int j=0; j<28; j++)
    {
        if(tabellone_[j].getOwner() == player)
        {
            tabellone_[j].reset();
        }
    }
}

void Game::payFees(int payer, int payee, int pos)
{
    int newFiorini;
    int amount;
    int level;
    std::string log = "";

    level = tabellone_[pos].getLevel();

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

    if (players_[payer].getFiorini() >= amount) 
    {
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
        players_[payer].setFiorini(0);
        remOwner(&players_[payer]);
        log = "Giocatore " + std::to_string(players_[payer].getId()) + " è stato eliminato";
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


int Game::rollDice(){
    static std::uniform_int_distribution<int> uid(1,12); 
    return uid(rng);
}


void Game::printBoard(){
    std::cout << "" <<
        "\t" << " 1" << "\t" << " 2" << "\t" << " 3" << "\t" << " 4" << "\t" << " 5" << "\t" << " 6" << "\t" << " 7" << "\t" << " 8" << "\t" <<
    std::endl;
    std::cout << "--------------------------------------------------------------------------------"
    << std::endl;
    std::cout << "A" << "\t";
    for(int i=14; i<22; i++){
        std::cout << "|" << tabellone_[i].getPropClass();
        std::cout << ((tabellone_[i].getLevel() == 1) ? "*" : "");
        std::cout << ((tabellone_[i].getLevel() == 2) ? "^" : "");
        for(int j=0; j<NO_PLAYERS; j++){
            if(players_[j].getPos() == i){
                std::cout << players_[j].getId();
            }
        }
        std::cout << "|" << "\t";
    }
    std::cout << std::endl;
    std::cout << "B" <<
        "\t" << 
        "|" << tabellone_[13].getPropClass();
        if(tabellone_[13].getLevel() == 1) std::cout << "*";
        if(tabellone_[13].getLevel() == 2) std::cout << "^";
        for(int j=0; j<NO_PLAYERS; j++){
            if(players_[j].getPos() == 13){
                std::cout << players_[j].getId();
            }
        }
        std::cout << "|" << 
        "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone_[22].getPropClass(); 
        if(tabellone_[22].getLevel() == 1) std::cout << "*";
        if(tabellone_[22].getLevel() == 2) std::cout << "^";
        for(int j=0; j<NO_PLAYERS; j++){
            if(players_[j].getPos() == 22){
                std::cout << players_[j].getId();
            }
        }
        std::cout << "|" << "\t" <<
    std::endl;
    std::cout << "C" <<
        "\t" << 
        "|" << tabellone_[12].getPropClass();
        if(tabellone_[12].getLevel() == 1) std::cout << "*";
        if(tabellone_[12].getLevel() == 2) std::cout << "^";
        for(int j=0; j<NO_PLAYERS; j++){
            if(players_[j].getPos() == 12){
                std::cout << players_[j].getId();
            }
        }
        std::cout << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone_[23].getPropClass();
        if(tabellone_[23].getLevel() == 1) std::cout << "*";
        if(tabellone_[23].getLevel() == 2) std::cout << "^";
        for(int j=0; j<NO_PLAYERS; j++){
            if(players_[j].getPos() == 23){
                std::cout << players_[j].getId();
            }
        }
        std::cout << "|" << "\t" <<
    std::endl;
    std::cout << "D" <<
        "\t" << 
        "|" << tabellone_[11].getPropClass();
        if(tabellone_[11].getLevel() == 1) std::cout << "*";
        if(tabellone_[11].getLevel() == 2) std::cout << "^";
        for(int j=0; j<NO_PLAYERS; j++){
            if(players_[j].getPos() == 11){
                std::cout << players_[j].getId();
            }
        }
        std::cout << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone_[24].getPropClass();
        if(tabellone_[24].getLevel() == 1) std::cout << "*";
        if(tabellone_[24].getLevel() == 2) std::cout << "^";
        for(int j=0; j<NO_PLAYERS; j++){
            if(players_[j].getPos() == 24){
                std::cout << players_[j].getId();
            }
        }
        std::cout << "|" << "\t" <<
    std::endl;
    std::cout << "E" <<
        "\t" << 
        "|" << tabellone_[10].getPropClass();
        if(tabellone_[10].getLevel() == 1) std::cout << "*";
        if(tabellone_[10].getLevel() == 2) std::cout << "^";
        for(int j=0; j<NO_PLAYERS; j++){
            if(players_[j].getPos() == 10){
                std::cout << players_[j].getId();
            }
        }
        std::cout << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone_[25].getPropClass();
        if(tabellone_[25].getLevel() == 1) std::cout << "*";
        if(tabellone_[25].getLevel() == 2) std::cout << "^";
        for(int j=0; j<NO_PLAYERS; j++){
            if(players_[j].getPos() == 25){
                std::cout << players_[j].getId();
            }
        }
        std::cout << "|" << "\t" <<
    std::endl;
    std::cout << "F" <<
        "\t" << "|" << tabellone_[9].getPropClass();
        if(tabellone_[9].getLevel() == 1) std::cout << "*";
        if(tabellone_[9].getLevel() == 2) std::cout << "^";
        for(int j=0; j<NO_PLAYERS; j++){
            if(players_[j].getPos() == 9){
                std::cout << players_[j].getId();
            }
        }
        std::cout << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone_[26].getPropClass();
        if(tabellone_[26].getLevel() == 1) std::cout << "*";
        if(tabellone_[26].getLevel() == 2) std::cout << "^";
        for(int j=0; j<NO_PLAYERS; j++){
            if(players_[j].getPos() == 26){
                std::cout << players_[j].getId();
            }
        }
        std::cout << "|" << "\t" <<
    std::endl;
    std::cout << "G" <<
        "\t" << "|" << tabellone_[8].getPropClass();
        if(tabellone_[8].getLevel() == 1) std::cout << "*";
        if(tabellone_[8].getLevel() == 2) std::cout << "^";
        for(int j=0; j<NO_PLAYERS; j++){
            if(players_[j].getPos() == 8){
                std::cout << players_[j].getId();
            }
        }
        std::cout << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone_[27].getPropClass();
        if(tabellone_[27].getLevel() == 1) std::cout << "*";
        if(tabellone_[27].getLevel() == 2) std::cout << "^";
        for(int j=0; j<NO_PLAYERS; j++){
            if(players_[j].getPos() == 27){
                std::cout << players_[j].getId();
            }
        }
        std::cout << "|" << "\t" <<
    std::endl;
    std::cout << "H" << "\t";
        for(int i=7; i>=0; i--){
            std::cout << "|" << tabellone_[i].getPropClass();
            std::cout << ((tabellone_[i].getLevel() == 1) ? "*" : "");
            std::cout << ((tabellone_[i].getLevel() == 2) ? "^" : "");
            for(int j=0; j<NO_PLAYERS; j++){
                if(players_[j].getPos() == i){
                    std::cout << players_[j].getId();
                }
            }
            std::cout << "|" << "\t";
        }
    std::cout << std::endl;
    std::cout << std::endl;
}


void Game::printProps()
{
    std::cout << "Caselle possedute dai giocatori: " << std::endl;
    for(int i=0; i<NO_PLAYERS; i++)
    {
        std::cout << "\tGiocatore " << i+1 << ": ";
        for(int j=0; j<28; j++)
        {
            if(tabellone_[j].getOwner() == &players_[i])
            {
                std::cout << tabellone_[j].getLegenda() << " ";
            }
        }
        std::cout << std::endl;
    }
}
