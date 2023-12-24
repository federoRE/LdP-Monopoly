#ifndef CIRCULAR_ARRAY_H
#define CIRCULAR_ARRAY_H

#include <vector>

/**
 * TODO: aggiungere override operatore []
*/

template<class T>
class CircularArray
{
private:
    std::vector<T> data_;
    int front_;
    int rear_;

public:
    /**
     * @brief Construct a new Circular Array object
     * 
    */
    CircularArray() : front_(0), rear_(0) {};

    /**
     * @brief Get the size of the array
     * @return Size of the array
     * 
    */
    int size() const;

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
