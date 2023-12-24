#ifndef CIRCULAR_ARRAY_H
#define CIRCULAR_ARRAY_H

#include <vector>

/**
 * TODO: non si puo' usare push con dimensione fissata, perche' 
 *      li mette in coda e non in testa
*/

template<class T>
class CircularArray
{
private:
    std::vector<T> data_;
    int front_;
    int rear_;
    int size_;

public:

    /**
     * @brief Construct a new Circular Array object
     * 
     */
    CircularArray() : front_(0), rear_(0), size_(0) {};
    
    /**
     * @brief Construct a new Circular Array object with a fixed size
     * 
     * @param size The fixed size of the array
     */
    CircularArray(int size) : front_(0), rear_(0), size_(size) {
        data_.resize(size_);
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
     * @brief Get an iterator pointing to the first element of the array
     * @return Iterator pointing to the first element
     * 
    */
    typename std::vector<T>::iterator begin();

    /**
     * @brief Get an iterator pointing to the last element of the array
     * @return Iterator pointing to the last element
     * 
    */
    typename std::vector<T>::iterator end();

    /**
     * @brief Get the element at the specified index
     * @param index Index of the element
     * @return Element at the specified index
     * 
    */
    T get(int index) const;

    /**
     * @brief Get the element at the specified index
     * @param index Index of the element
     * @return Element at the specified index
     * 
    */
    T operator[](int index) const;

    /**
     * @brief Overload the assignment operator
     * @param other The CircularArray object to assign from
     * @return Reference to the assigned CircularArray object
     */
    CircularArray& operator=(const CircularArray& other);

    /**
     * @brief Move constructor for CircularArray
     * @param other The CircularArray object to move from
     */
    CircularArray(CircularArray&& other) noexcept;

    };

#endif // CIRCULAR_ARRAY_H
