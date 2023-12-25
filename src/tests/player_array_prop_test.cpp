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

    std::cout << "Tabellone" << std::endl;
    std::cout << "" << 
        tabellone[14].getPropClass() << "\t" <<
        tabellone[15].getPropClass() << "\t" <<
        tabellone[16].getPropClass() << "\t" <<
        tabellone[17].getPropClass() << "\t" <<
        tabellone[18].getPropClass() << "\t" <<
        tabellone[19].getPropClass() << "\t" <<
        tabellone[20].getPropClass() << "\t" <<
        tabellone[21].getPropClass() << "\t" <<
    std::endl;
    std::cout << "" <<
        tabellone[13].getPropClass() << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        tabellone[22].getPropClass() << "\t" <<
    std::endl;
    std::cout << "" <<
        tabellone[12].getPropClass() << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        tabellone[23].getPropClass() << "\t" <<
    std::endl;
    std::cout << "" <<
        tabellone[11].getPropClass() << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        tabellone[24].getPropClass() << "\t" <<
    std::endl;
    std::cout << "" <<
        tabellone[10].getPropClass() << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        tabellone[25].getPropClass() << "\t" <<
    std::endl;
    std::cout << "" <<
        tabellone[9].getPropClass() << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        tabellone[26].getPropClass() << "\t" <<
    std::endl;
    std::cout << "" <<
        tabellone[8].getPropClass() << "\t" << " " <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        "\t" <<
        tabellone[27].getPropClass() << "\t" <<
    std::endl;
    std::cout << "" << 
        tabellone[7].getPropClass() << "\t" <<
        tabellone[6].getPropClass() << "\t" <<
        tabellone[5].getPropClass() << "\t" <<
        tabellone[4].getPropClass() << "\t" <<
        tabellone[3].getPropClass() << "\t" <<
        tabellone[2].getPropClass() << "\t" <<
        tabellone[1].getPropClass() << "\t" <<
        tabellone[0].getPropClass() << "\t" <<
    std::endl;


    return 0;
}