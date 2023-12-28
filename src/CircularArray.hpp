#ifndef CIRCULAR_ARRAY_HPP
#define CIRCULAR_ARRAY_HPP

#include <stdexcept>
#include <random>
#include <algorithm>

#include "CircularArray.h"

template<class T>
int CircularArray<T>::size() const
{
    return size_;
}

template<class T>
void CircularArray<T>::push(T value)
{
    if (
        (front_ == 0 && rear_ == size_ - 1) || 
        ((rear_ +1) % size_ == front_)
    )
    {
        return;
    }

    if (front_ == -1)
    {
        front_ = rear_ = 0;
        data_[rear_] = value;
    }
    else if (rear_ == size_ - 1 && front_ != 0)
    {
        rear_ = 0;
        data_[rear_] = value;
    }
    else
    {
        rear_++;
        data_[rear_] = value;
    }

    return;
}


// da rivedere i parsing e casting
template<class T>
T CircularArray<T>::pop()
{
    if (isEmpty())
    {
        return T(); // Return a default-constructed object of type T
    }

    T value = data_[front_];
    data_[front_] = -1;

    if (front_ == rear_)
    {
        front_ = -1;
        rear_ = -1;
    }
    else if (front_ == size_ - 1)
    {
        front_ = 0;
    }
    else
    {
        front_++;
    }

    return value;
}

template<class T>
bool CircularArray<T>::isFull() const
{
    return !isEmpty();
}

template<class T>
bool CircularArray<T>::isEmpty() const
{
    return front_ == -1;
}

template<class T>
void CircularArray<T>::shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data_, data_ + size_, g);
}

template<class T>
T CircularArray<T>::get(int index) const
{
    return data_[index%data_.size()];
}

template<class T>
void CircularArray<T>::swap(int index1, int index2)
{
    if (index1 < 0 || index1 >= size_ || index2 < 0 || index2 >= size_)
    {
        throw std::out_of_range("Index out of range");
    }

    T temp(data_[index1]); // Use copy constructor to create a new instance of T
    data_[index1] = data_[index2];
    data_[index2] = temp;
}

template<class T>
T& CircularArray<T>::operator[](int index)
{
    return data_[index % size_];
}


template<class T>
CircularArray<T>& CircularArray<T>::operator=(const CircularArray& other)
{
    if (this != &other)
    {
        data_ = other.data_;
        front_ = other.front_;
        rear_ = other.rear_;
    }
    return *this;
}

template<class T>
CircularArray<T>::CircularArray(const CircularArray& other)
{
    data_ = other.data_;
    front_ = other.front_;
    rear_ = other.rear_;
}

template<class T>
CircularArray<T>::CircularArray(CircularArray&& other) noexcept
{
    data_ = std::move(other.data_);
    front_ = other.front_;
    rear_ = other.rear_;
    other.front_ = 0;
    other.rear_ = 0;
}


template<class T>
CircularArray<T>::~CircularArray()
{
    delete[] data_;
}


#endif // CIRCULAR_ARRAY_HPP