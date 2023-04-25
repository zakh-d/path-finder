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

    void push_back(T elem)
    {
        if (size == max_size)
        {
            expand();
        }
        array[size++] = elem;
    }

    T operator[](std::size_t index)
    {
        return array[index];
    }

    std::size_t getSize() {
        return size;
    }

    ~Vector()
    {
        delete[] array;
    }
};