#include "PropertyArray.h"
#include "Property.h"

#include <iostream>

int main(int argc, char* argv[]){
    PropertyArray prop_array;

    prop_array.push(std::move(Property('L', 100, 50, 50, 10, 20)));
    prop_array.push(std::move(Property('M', 200, 100, 100, 20, 40)));
    prop_array.push(std::move(Property('H', 300, 150, 150, 30, 60)));

    std::cout << "Size: " << prop_array.size() << std::endl;
    std::cout << "Is full: " << (prop_array.isFull()?"true" : "false") << std::endl;

    for(int i=0; i<prop_array.size(); i++){
        std::cout << "Property " << i << " class: " << prop_array[i].getPropClass() << std::endl;
    }

    std::cout << "Shuffle" << std::endl;

    // Shuffle
    prop_array.shuffle();
    for(int i=0; i<prop_array.size(); i++){
        std::cout << "Property " << i << " class: " << prop_array[i].getPropClass() << std::endl;
    }

    // Test con costruttore indice
    PropertyArray prop_array2(3);
    prop_array2.push(Property('L', 100, 50, 50, 10, 20));
    prop_array2.push(Property('M', 200, 100, 100, 20, 40));
    prop_array2.push(Property('H', 300, 150, 150, 30, 60));

    std::cout << "Size: " << prop_array2.size() << std::endl;
    for(int i=0; i<prop_array2.size(); i++){
        std::cout << "Property " << i << " class: " << prop_array2[i].getPropClass() << std::endl;
    }

    return 0;
}