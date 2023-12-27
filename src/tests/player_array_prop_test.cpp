#include "CircularArray.h"
#include "Property.h"

#include <iostream>

int main(int argc, char* argv[]){
    /////////////////////////////
    // Test funzionamento di base
    /////////////////////////////

    std::cout << "Test funzionamento di base" << std::endl;

    CircularArray<Property> prop_array3(24);
    // Economic
    for(int i=0; i<8; i++){
        prop_array3.push(std::move(Property('E', 6, 3, 3, 2, 4)));
    }
    // Standard
    for(int i=0; i<10; i++){
        prop_array3.push(Property('S', 10, 5, 5, 4, 8));
    }
    // Luxury
    const int numIterations = 6;
    for(int i=0; i<numIterations; i++){
        prop_array3.push(Property('L', 20, 10, 10, 7, 14));
    }
    prop_array3.shuffle();
    

    std::cout << "inizio a comporre il tabellone" << std::endl;
    CircularArray<Property> tabellone(28);

    tabellone.push(std::move(Property('P', 0, 0, 0, 0, 0)));
    for(int i=0; i<24; i++){
        tabellone.push(std::move(prop_array3[i]));
        if((i+1) % 6 == 0) {
            tabellone.push(std::move(Property(' ', 0, 0, 0, 0, 0)));
        }
    }


    // Creo la cell id legenda
    std::string *cell_ids = new std::string[28];
    cell_ids[0] = "H8"; 
    cell_ids[1] = "H7";
    cell_ids[2] = "H6";
    cell_ids[3] = "H5";
    cell_ids[4] = "H4";
    cell_ids[5] = "H3";
    cell_ids[6] = "H2";
    cell_ids[7] = "H1";
    cell_ids[8] = "G1";
    cell_ids[9] = "F1";
    cell_ids[10] = "E1";
    cell_ids[11] = "D1";
    cell_ids[12] = "C1";
    cell_ids[13] = "B1";
    cell_ids[14] = "A1";
    cell_ids[15] = "A2";
    cell_ids[16] = "A3";
    cell_ids[17] = "A4";
    cell_ids[18] = "A5";
    cell_ids[19] = "A6";
    cell_ids[20] = "A7";
    cell_ids[21] = "A8";
    cell_ids[22] = "B8";
    cell_ids[23] = "C8";
    cell_ids[24] = "D8";
    cell_ids[25] = "E8";
    cell_ids[26] = "F8";
    cell_ids[27] = "G8";
    constexpr const char* coordinates = "H8H7H6H5H4H3H2H1G1F1E1D1C1B1A1A2A3A4A5A6A7A8B8C8D8E8F8G8";

    for(int i=0; i<28; i++){
        tabellone[i].setLegenda(cell_ids[i]);
    }


    std::cout << "Tabellone" << std::endl;
    std::cout << "" << 
        "\t" << "1" << "\t" <<
        "2" << "\t" <<
        "3" << "\t" <<
        "4" << "\t" <<
        "5" << "\t" <<
        "6" << "\t" <<
        "7" << "\t" <<
        "8" << "\t" <<
    std::endl;
    std::cout << "--------------------------------------------------------------------------------"
    << std::endl;
    std::cout << "A" << 
        "\t" << "|" << tabellone[14].getPropClass() << "|" << "\t" <<
        "|" << tabellone[15].getPropClass() << "|" << "\t" <<
        "|" << tabellone[16].getPropClass() << "|" << "\t" <<
        "|" << tabellone[17].getPropClass() << "|" << "\t" <<
        "|" << tabellone[18].getPropClass() << "|" << "\t" <<
        "|" << tabellone[19].getPropClass() << "|" << "\t" <<
        "|" << tabellone[20].getPropClass() << "|" << "\t" <<
        "|" << tabellone[21].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "B" <<
        "\t" << "|" << tabellone[13].getPropClass() << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone[22].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "C" <<
        "\t" << "|" << tabellone[12].getPropClass() << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone[23].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "D" <<
        "\t" << "|" << tabellone[11].getPropClass() << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone[24].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "E" <<
        "\t" << "|" << tabellone[10].getPropClass() << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone[25].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "F" <<
        "\t" << "|" << tabellone[9].getPropClass() << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone[26].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "G" <<
        "\t" << "|" << tabellone[8].getPropClass() << "|" << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "|" << tabellone[27].getPropClass() << "|" << "\t" <<
    std::endl;
    std::cout << "H" << 
        "\t" << "|" << tabellone[7].getPropClass() << "|" << "\t" <<
        "|" << tabellone[6].getPropClass() << "|" << "\t" <<
        "|" << tabellone[5].getPropClass() << "|" << "\t" <<
        "|" << tabellone[4].getPropClass() << "|" << "\t" <<
        "|" << tabellone[3].getPropClass() << "|" << "\t" <<
        "|" << tabellone[2].getPropClass() << "|" << "\t" <<
        "|" << tabellone[1].getPropClass() << "|" << "\t" <<
        "|" << tabellone[0].getPropClass() << "|" << "\t" <<
    std::endl;

    Player *players = new Player[4];
    players[0] = Player();
    players[1] = Player();
    players[2] = Player();
    players[3] = Player();
    players[0].setName("Player 1");
    players[1].setName("Player 2");
    players[2].setName("Player 3");
    players[3].setName("Player 4");

    std::cout << "Player 1: " << players[0].getName() << std::endl;

    return 0;
}