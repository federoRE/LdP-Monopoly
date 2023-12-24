#ifndef CIRCULAR_ARRAY_H
#define CIRCULAR_ARRAY_H

#include <stdexcept>

const int SIZE = 28;

/**
 * @brief Circular array
 * 
 * @tparam T Type of the array
 * 
*/
template <class T>
class CircularArray
{
private:
    T data_[SIZE];
    int front_;
    int rear_;

public:
    /**
     * @brief Construct a new Circular Array object
     * 
    */
    CircularArray() : front_(0), rear_(0) {}

    /**
     * @brief Insert element in the array
     * @param value Element to insert
     * 
    */
    void push(T value);

    /**
     * @brief Remove element from the array
     * @return Element removed
     * 
    */
    T pop();

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



#endif // CIRCULAR_ARRAY_H