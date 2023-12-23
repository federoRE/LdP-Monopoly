#ifndef CIRCULAR_ARRAY_H
#define CIRCULAR_ARRAY_H

#include <string>
#include <stdexcept>

const int SIZE = 28;

class CircularArray
{
private:
    std::string data_[SIZE];
    int front_;
    int rear_;

public:
    CircularArray() : front_(0), rear_(0) {}

    /**
     * @brief Insert element in the array
     * @param value Element to insert
     * 
    */
    void push(std::string value);

    /**
     * @brief Remove element from the array
     * @return Element removed
     * 
    */
    std::string pop();

    /**
     * @brief Check if the array is full
     * @return True if the array is full, false otherwise
     * 
    */
    bool isFull() const;

    /**
     * @brief Check if the array is empty
     * @return True if the array is empty, false otherwise
     * 
    */
    bool isEmpty() const;

};

/*
CircularArray::CircularArray(/* args)
{
}

CircularArray::~CircularArray()
{
}
*/

#endif // CIRCULAR_ARRAY_H