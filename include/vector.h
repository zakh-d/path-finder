#pragma once

#define DEFAULT_SIZE 10

template <typename T>
class Vector {
    T* array;
    std::size_t size;
    std::size_t max_size;
    void expand()
    {
        T* new_array = new T[max_size*4];
        for (int i = 0; i < size; i++)
        {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
        max_size = max_size * 4;
    }
public:

    Vector()
    : array(new T[DEFAULT_SIZE]), size(0), max_size(DEFAULT_SIZE){

    }

    Vector(const Vector& other)
    : array(new T[other.max_size]), size(other.size), max_size(other.max_size){
        for (int i = 0; i < size; i++)
        {
            array[i] = other.array[i];
        }
    }

    Vector(Vector&& other)
    : array(other.array), size(other.size), max_size(other.max_size){
        other.array = nullptr;
        other.size = 0;
        other.max_size = 0;
    }

    Vector(std::size_t n)
    : array(new T[n]), size(n), max_size(n){}

    Vector(std::size_t n, T default_value)
    : Vector(n) {
        for (std::size_t i = 0; i < size; i++)
        {
            array[i] = default_value;
        }
    }

    void push_back(T elem)
    {
        if (size == max_size)
        {
            expand();
        }
        array[size++] = elem;
    }

    void reverse()
    {
        for (int i = 0; i < size / 2; i++)
        {
            std::swap(array[i], array[size - i - 1]);
        }
    }

    T& operator[](std::size_t index)
    {
        return array[index];
    }

    T operator[](std::size_t index) const
    {
        return array[index];
    }

    Vector<T>& operator=(const Vector& other)
    {
        Vector<T> tmp(other);
        std::swap(array, tmp.array);
        std::swap(size, tmp.size);
        std::swap(max_size, tmp.max_size);
        return *this;
    }

    std::size_t getSize() const {
        return size;
    }

    ~Vector()
    {
        delete[] array;
    }
};