#include "CircularArray.h"
#include "Property.h"

#include <iostream>

int main(int argc, char* argv[]){
    CircularArray prop_array;
    Property prop1('L', 100, 50, 50, 10, 20);
    Property prop2('L', 100, 50, 50, 10, 20);
    prop_array.push(prop1);
    prop_array.push(prop2);
    std::cout << (prop_array.isEmpty() ? "true" : "false") << std::endl;


    return 0;
}