#ifndef CIRCULAR_ARRAY_H
#define CIRCULAR_ARRAY_H

#include <algorithm>
#include <random>

#include <memory>


template<class T>
class CircularArray
{
private:
    std::shared_ptr<T[]> data_; // Pointer to the data stores
    int front_; // Index of the front element
    int rear_; // Index of the rear element
    int size_; // Size of the array

public:

    /**
     * @brief Construct a new Circular Array object
     * 
     */
    CircularArray() : 
        front_(-1), 
        rear_(-1), 
        size_(1) 
        {
            data_ = std::shared_ptr<T[]>(new T[size_]);
        };
        
    /**
     * @brief Construct a new Circular Array object with a fixed size
     * 
     * @param size The fixed size of the array
     */
    CircularArray(int size) : 
        front_(-1), 
        rear_(-1), 
        size_(size) 
        {
            data_ = std::shared_ptr<T[]>(new T[size_]);
        };

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

    /**
     * @brief Shuffle the elements in the array
     * 
     */
    void shuffle();

    /**
     * Swaps the elements at the specified indices.
     *
     * @param index1 The index of the first element to swap.
     * @param index2 The index of the second element to swap.
     * @throws std::out_of_range if either index is out of bounds.
     */
    void swap(int index1, int index2);

    /**
     * @brief Get the raw pointer to the array
     * @return Raw pointer to the array
    */
    T* get() const;

    /**
     * @brief Get the element at the specified index
     * @param index Index of the element
     * @return Element at the specified index
    */
    T* get(int index) const;

    /**
     * @brief Overload the subscript operator
     * @param index The index of the element to access
     * @return Reference to the element at the specified index
     * @throws std::out_of_range if the index is out of bounds
    */
    T& operator[](int index);

    /**
     * @brief Overload the assignment operator
     * @param other The CircularArray object to assign from
     * @return Reference to the assigned CircularArray object
     */
    CircularArray& operator=(const CircularArray& other);

    /**
     * @brief Copy constructor for CircularArray
     * @param other The CircularArray object to copy from
     */
    CircularArray(const CircularArray& other);

    /**
     * @brief Move constructor for CircularArray
     * @param other The CircularArray object to move from
     */
    CircularArray(CircularArray&& other) noexcept;
    
    /**
     * @brief Destructor for CircularArray
     */
    ~CircularArray();


    // Test iteratori
    T* begin();
    T* end();
};

#include "CircularArray.hpp"

#endif // CIRCULAR_ARRAY_H
