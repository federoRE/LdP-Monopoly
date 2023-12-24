#include "CircularArray.h"

#include <iostream>

int main(int argc, char* argv[]){
    CircularArray<std::string> prop_array;
    prop_array.push("ciao");
    std::cout << prop_array.pop() << std::endl;


    return 0;
}