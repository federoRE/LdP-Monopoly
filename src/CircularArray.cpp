#include "CircularArray.h"
#include <stdexcept>

template <class T>
void CircularArray<T>::push(T value)
{
    if (isFull())
    {
        throw std::runtime_error("Array pieno!");
    }
    data_[rear_] = value;
    rear_ = (rear_ + 1) % SIZE;
}

template <class T>
T CircularArray<T>::pop()
{
    if (isEmpty())
    {
        throw std::runtime_error("Array vuoto!");
    }
    T value = data_[front_];
    front_ = (front_ + 1) % SIZE;
    return value;
}

template <class T>
bool CircularArray<T>::isFull() const
{
    return ((rear_ + 1) % SIZE == front_);
}

template <class T>
bool CircularArray<T>::isEmpty() const
{
    return (front_ == rear_);
}

