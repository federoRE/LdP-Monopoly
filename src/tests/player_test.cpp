#include "Player.h"
#include <cassert>

int main(){
    Player p1(false);
    Player p2(true);

    // Test costruttore
    assert(p1.getPos() == 0);
    assert(p1.getFiorini() == 0);
    assert(p1.getRoll() == 0);
    assert(p1.isBot() == false);

    assert(p2.getPos() == 0);
    assert(p2.getFiorini() == 0);
    assert(p2.getRoll() == 0);
    assert(p2.isBot() == true);

    // Test setter
    p1.setPos(1);
    p1.setFiorini(2);
    p1.setRoll(3);

    assert(p1.getPos() == 1);
    assert(p1.getFiorini() == 2);
    assert(p1.getRoll() == 3);

    // Test getter
    assert(p1.getPos() == 1);
    assert(p1.getFiorini() == 2);
    assert(p1.getRoll() == 3);

    // Test incPos
    p1.incPos(1);
    assert(p1.getPos() == 2);

    // Test isLose
    assert(p1.isLose() == false);
    p1.setFiorini(0);
    assert(p1.isLose() == true);

    return 0;
}