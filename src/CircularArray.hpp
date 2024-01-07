#ifndef CIRCULAR_ARRAY_HPP
#define CIRCULAR_ARRAY_HPP

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
        // se la coda e' piena
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
        return T(); // return default value of T
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
    return (front_ == 0 && rear_ == size_ - 1) || 
        ((rear_ +1) % size_ == front_);
}

template<class T>
bool CircularArray<T>::isEmpty() const
{
    return front_ == -1;
}

template<class T>
void CircularArray<T>::shuffle()
{
    // usato solamente dal Property
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(data_.get(), data_.get() + size_, rng);
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
T* CircularArray<T>::get() const
{
    return data_.get();
}


template<class T>
T* CircularArray<T>::get(int index) const
{
    return &data_[index % size_];
}


template<class T>
T& CircularArray<T>::operator[](int index)
{
    int realIndex = (front_ + index) % size_;
    return data_[realIndex];
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
    data_.reset();
}


template<class T>
T* CircularArray<T>::begin()
{
    return &data_[front_];
}


template<class T>
T* CircularArray<T>::end()
{
    return &data_[rear_];
}


#endif // CIRCULAR_ARRAY_HPP