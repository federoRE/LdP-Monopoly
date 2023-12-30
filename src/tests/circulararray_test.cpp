#include "CircularArray.h"
#include <iostream>

void testSize() {
    CircularArray<int> array(5);
    if (array.size() != 5) {
        throw std::runtime_error("Size test failed");
    }

    array.push(1);
    array.push(2);
    array.push(3);
    array.push(4);
    array.push(5);
    
    if(!array.isFull()){
        throw std::runtime_error("Size test failed");
    }

    // Aggiungi altri test secondo le tue necessità
}

void testPushPop() {
    CircularArray<int> array(3);

    array.push(1);
    array.push(2);
    array.push(3);

    if (!array.isFull()) {
        throw std::runtime_error("PushPop test failed");
    }

    array.pop();
    if (array.isFull()) {
        throw std::runtime_error("PushPop test failed");
    }

    // Aggiungi altri test secondo le tue necessità
}

int main(int argc, char* argv[]) {
    try {
        testSize();
        testPushPop();
        // Aggiungi altri test secondo le tue necessità
        std::cout << "All tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
