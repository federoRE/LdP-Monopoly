#include <stdexcept>
#include "CircularArray.h"

template<class T>
int CircularArray<T>::size() const
{
    return data_.size();
}

template<class T>
void CircularArray<T>::push(T value)
{
    data_.push_back(value);
    rear_ = (rear_ + 1) % data_.size();
}

template<class T>
T CircularArray<T>::pop()
{
    if (isEmpty())
    {
        throw std::runtime_error("CircularArray is empty");
    }

    T value = data_[front_];
    front_ = (front_ + 1) % data_.size();
    return value;
}

template<class T>
bool CircularArray<T>::isFull() const
{
    return (rear_ + 1) % data_.size() == front_;
}

template<class T>
bool CircularArray<T>::isEmpty() const
{
    return front_ == rear_;
}

template<class T>
T CircularArray<T>::get(int index) const
{
    return data_[index];
}

template<class T>
T CircularArray<T>::operator[](int index) const
{
    return data_[index];
}