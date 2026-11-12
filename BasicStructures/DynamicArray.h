#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>

template <class T>
class DynamicArray
{
private:
    T* array = nullptr;
    int capacity;
    int length;

public:
    DynamicArray(T* items, int count, int buffer_size)
    {
        capacity = buffer_size;
        length = count;
        array = new T[buffer_size];
        for (int ii = 0; ii < count; ii++)
        {
            array[ii] = items[ii];
        }
    }

    DynamicArray(T* items, int count)
    {
        capacity = count;
        length = count;
        array = new T[count + 1];
        for (int ii = 0; ii < count; ii++)
        {
            array[ii] = items[ii];
        }
    }

    DynamicArray(int buffer_size)
    {
        capacity = buffer_size;
        length = 0;
        if (buffer_size > 0)
        {
            array = new T[buffer_size + 1];
        }
        if (buffer_size == 0)
        {
            capacity = 1;
            array = new T[capacity];
        }
    }

    DynamicArray()
    {
        capacity = 1;
        length = 0;
        array = new T[capacity];
    }

    DynamicArray(const DynamicArray<T>& other_array)
    {
        capacity = other_array.capacity;
        length = other_array.length;
        array = new T[other_array.capacity + 1];
        array = other_array.array;
    }

    DynamicArray& operator = (const DynamicArray<T>& other_array)
    {
        if (array != nullptr)
        {
            delete[] array;
        }
        capacity = other_array.capacity;
        length = other_array.length;
        array = new T[other_array.capacity + 1];
        for (int ii = 0; ii < capacity; ii++)
        {
            array[ii] = other_array.array[ii];
        }
        return *this;
    }

    DynamicArray(DynamicArray<T>&& other_array)
    {
        capacity = other_array.capacity;
        length = other_array.length;
        array = other_array.array;
        other_array.capacity = 0;
        other_array.length = 0;
        other_array.array = nullptr;
    }

    DynamicArray& operator = (DynamicArray<T>&& other_array)
    {
        if (array != nullptr)
        {
            delete[] array;
        }
        capacity = other_array.capacity;
        length = other_array.length;
        array = other_array.array;
        other_array.capacity = 0;
        other_array.length = 0;
        other_array.array = nullptr;
        return *this;
    }

    ~DynamicArray()
    {
        if (array != nullptr)
        {   
            delete[] array;
        }
    }

    T Get(int index) const
    {
        T elem;
        if (index < 0 || index >= length)
        {
            std::cout << index;
            throw std::out_of_range("Index out of range\n");
        }
        else
        {
            elem = array[index];
        }
        return elem;
    }

    int GetCapacity() const
    {
        return capacity;
    }

    int GetLength() const
    {
        return length;
    }

    T* GetArray() const
    {
        return array;
    }

    void SetLength(int new_length)
    {
        length = new_length;
    }

    void Set(const T& item, int index)
    {
        if (index < 0 || index >= capacity)
        {
            throw std::out_of_range("Index out of range\n");
        }
        array[index] = item;
        if (index == length)
        {
            length++;
        }
    }

    DynamicArray<T>* GetSubArray(int start_index, int end_index)
    {
        int size = end_index - start_index + 1;
        T* temp_array = new T[size];
        for (int ii = start_index; ii <= end_index; ii++)
        {
            temp_array[ii - start_index] = array[ii];
        }
        DynamicArray<T>* new_array = new DynamicArray<T>(temp_array, size, size);
        delete[] temp_array;
        return(new_array);
    }

    void Resize(int new_size)
    {
        T* new_array = new T[new_size];
        if (capacity >= new_size)
        {
            for (int ii = 0; ii < new_size; ii++)
            {
                new_array[ii] = array[ii];
            }
        }
        if (capacity < new_size)
        {
            for (int ii = 0; ii < capacity; ii++)
            {
                new_array[ii] = array[ii];
            }
        }
        //delete[] array;
        array = new_array;
        capacity = new_size;
    }
};

template <class T>
std::ostream& operator << (std::ostream& stream, const DynamicArray<T>& array)
{

    for (int ii = 0; ii < array.GetLength(); ii++)
    {
        stream << array.Get(ii) << " ";
    }
    stream << std::endl;
    return stream;
}

#endif