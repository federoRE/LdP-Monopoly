#include "CircularArray.h"
#include <stdexcept>

void CircularArray::push(Property value)
{
    if (isFull())
    {
        throw std::runtime_error("Array pieno!");
    }
    data_[rear_] = value;
    rear_ = (rear_ + 1) % SIZE;
}


Property CircularArray::pop()
{
    if (isEmpty())
    {
        throw std::runtime_error("Array vuoto!");
    }
    Property value = data_[front_];
    front_ = (front_ + 1) % SIZE;
    return value;
}

bool CircularArray::isFull() const
{
    return ((rear_ + 1) % SIZE == front_);
}

bool CircularArray::isEmpty() const
{
    return (front_ == rear_);
}

