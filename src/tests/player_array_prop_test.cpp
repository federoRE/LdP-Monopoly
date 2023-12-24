#include "PropertyArray.h"
#include "Property.h"

#include <iostream>

int main(int argc, char* argv[]){
    PropertyArray prop_array;
    Property prop1('L', 100, 50, 50, 10, 20);
    Property prop2('L', 100, 50, 50, 10, 20);
    prop_array.push(prop1);
    prop_array.push(prop2);
    std::cout << (prop_array.isEmpty() ? "true" : "false") << std::endl;

    // Genero 24 elementi
    // Test con modulo
    if(25+8>28)
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    return 0;
}