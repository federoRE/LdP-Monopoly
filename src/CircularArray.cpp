#include <stdexcept>
#include <random>

#include "CircularArray.h"

template<class T>
int CircularArray<T>::size() const
{
    return data_.size();
}

template<class T>
void CircularArray<T>::push(T value)
{
    if (isEmpty())
    {
        data_.push_back(value);
        rear_ = (rear_ + 1) % data_.size();
    }
    else
    {
        // controllare se funziona dopo che hai fatto il primo push
        int insertIndex = (front_ + 1) % data_.size();
        data_.insert(data_.begin() + insertIndex, value);
        rear_ = (rear_ + 1) % data_.size();
    }
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
void CircularArray<T>::shuffle()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, data_.size() - 1);

    for (int i = 0; i < data_.size(); i++)
    {
        int randomIndex = dis(gen);
        std::swap(data_[i], data_[randomIndex]);
    }
}


template<class T>
typename std::vector<T>::iterator CircularArray<T>::begin()
{
    return data_.begin();
}

template<class T>
typename std::vector<T>::iterator CircularArray<T>::end()
{
    return data_.end();
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
CircularArray<T>::CircularArray(CircularArray&& other) noexcept
{
    data_ = std::move(other.data_);
    front_ = other.front_;
    rear_ = other.rear_;
    other.front_ = 0;
    other.rear_ = 0;
}
