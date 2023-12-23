#include "Player.h"
#include "Property.h"
#include "CircularArray.h"

#include <iostream>

int main(){
    Player p1(false);
    Player p2(true);

    Property prop1('L', 20, 10, 10, 7, 14);
    Property prop2('S', 10, 5, 5, 4, 8);
    Property prop3('E', 6, 3, 3, 2, 4);

    //CircularArray<Property, 3> prop_array;

    return 0;
}