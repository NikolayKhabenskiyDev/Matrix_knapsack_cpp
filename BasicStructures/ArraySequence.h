#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include <iostream>
#include "DynamicArray.h"
#include "Sequence.h"

template <class T>
class ArraySequenceImmut : public Sequence<T>
{
protected:
    DynamicArray<T> array;

public:

    ArraySequenceImmut(T* items, int count, int buffer_size)
    {
        array = DynamicArray<T>(items, count, buffer_size);
    }

    ArraySequenceImmut(T* items, int count)
    {
        array = DynamicArray<T>(items, count);
    }

    ArraySequenceImmut(int size)
    {
        array = DynamicArray<T>(size);
    }

    ArraySequenceImmut()
    {
        array = DynamicArray<T>();
    }

    ArraySequenceImmut(const DynamicArray<T>& dynamic_array)
    {
        array = DynamicArray<T>(dynamic_array);
    }

    ArraySequenceImmut(const ArraySequenceImmut<T>& other_seq)
    {
        array = DynamicArray<T>(other_seq.array);
    }

    ArraySequenceImmut operator = (const ArraySequenceImmut<T>& other_seq)
    {
        array = DynamicArray<T>(*(other_seq.array));
        return *this;
    }

    ArraySequenceImmut(ArraySequenceImmut<T>&& other_seq) noexcept
    {
        array = other_seq.array;
        other_seq.array = DynamicArray<T>();
    }

    ArraySequenceImmut& operator = (ArraySequenceImmut<T>&& other_seq) noexcept
    {
        delete array;
        array = other_seq.array;
        other_seq.array = nullptr;
        return *this;
    }

    ArraySequenceImmut(Sequence<T>* other_seq)
    {
        array = DynamicArray<T>(other_seq->GetLength());
        for (int ii = 0; ii < other_seq->GetLength(); ii++)
        {
            array.Set(other_seq->Get(ii), ii);
        }
    }

    ArraySequenceImmut operator = (Sequence<T>* other_seq)
    {
        array = DynamicArray<T>(other_seq->GetLength());
        for (int ii = 0; ii < other_seq->GetLength(); ii++)
        {
            array.Set(other_seq->Get(ii), ii);
        }
    }

    T GetFirst() const override
    {
        return array.Get(0);
    }

    T GetLast() const override
    {
        int size = array.GetLength()-1;
        return array.Get(size);
    }

    T Get(int index) const override
    {
        return array.Get(index);
    }

    int GetSize() const
    {
        return array.GetCapacity();
    }

    int GetLength() const override
    {
        return array.GetLength();
    }

    DynamicArray<T>* GetArray()
    {
        return array;
    }

    Sequence<T>* Set(const T& item, int index) override
    {
        ArraySequenceImmut<T>* new_sequence = new ArraySequenceImmut<T>(this->array.GetArray(), this->GetLength());
        new_sequence->array.Set(item, index);
        return new_sequence;
    }

    Sequence<T>* GetSubsequence(int start_index, int end_index) override
    {
        ArraySequenceImmut<T>* new_sequence = new ArraySequenceImmut<T>(this->array.GetArray(), this->GetLength());
        new_sequence->array = *(this->array.GetSubArray(start_index, end_index));
        return new_sequence;
    }

    Sequence<T>* SetSubsequence(Sequence<T>* subsequence, int index) override
    {
        ArraySequenceImmut<T>* new_sequence = new ArraySequenceImmut<T>(this->array.GetArray(), this->GetLength());
        for (int ii = 0; ii = subsequence->GetLength(); ii++)
        {
            new_sequence->Set(subsequence->Get(ii), ii + index);
        }
        return new_sequence;
    }

    Sequence<T>* Append(const T& item) override
    {
        ArraySequenceImmut<T>* new_sequence = new ArraySequenceImmut<T>(this->array.GetArray(), this->GetLength());
        int capacity = array.GetCapacity();
        int length = array.GetLength() + 1;
        if (length > capacity)
        {
            if (capacity < 1000)
            {
                new_sequence->array.Resize(2 * capacity);
            }
            else
            {
                new_sequence->array.Resize(capacity + 1000);
            }
        }
        new_sequence->array.Set(item, length - 1);
        return new_sequence;
    }

    Sequence<T>* Prepend(const T& item) override
    {
        ArraySequenceImmut<T>* new_sequence = new ArraySequenceImmut<T>(this->array.GetArray(), this->GetLength());
        int capacity = array.GetCapacity();
        int length = array.GetLength() + 1;
        if (length > capacity)
        {
            if (capacity < 1000)
            {
                new_sequence->array.Resize(2 * capacity);
            }
            else
            {
                new_sequence->array.Resize(capacity + 1000);
            }
        }
        for (int ii = length - 2; ii >= 0; ii--)
        {
            new_sequence->array.Set(Get(ii), ii + 1);
        }
        new_sequence->array.Set(item, 0);
        return new_sequence;
    }

    Sequence<T>* Concatenate(Sequence<T>* OtherSeq) override
    {
        ArraySequenceImmut<T>* new_sequence = new ArraySequenceImmut<T>(this->array.GetArray(), this->GetLength());
        int length1 = new_sequence->GetLength();
        int length2 = OtherSeq->GetLength();
        if (length1 + length2 > new_sequence->array.GetCapacity())
        {
            new_sequence->array.Resize(length1 + length2);
        }
        for (int ii = length1; ii < (length1 + length2); ii++)
        {
            new_sequence->array.Set(OtherSeq->Get(ii - length1), ii);
        }
        return new_sequence;
    }

    Sequence<T>* InsertAt(const T& item, int index) override
    {
        ArraySequenceImmut<T>* new_sequence = new ArraySequenceImmut<T>(this->array.GetArray(), this->GetLength());
        int capacity = array.GetCapacity();
        int length = array.GetLength() + 1;
        if (length > capacity)
        {
            if (capacity < 1000)
            {
                new_sequence->array.Resize(2 * capacity);
            }
            else
            {
                new_sequence->array.Resize(capacity + 1000);
            }
        }
        for (int ii = length - 2; ii >= index; ii--)
        {
            new_sequence->array.Set(Get(ii), ii + 1);
        }
        new_sequence->array.Set(item, index);

        return new_sequence;
    }

    Sequence<T>* Map(T(*func) (const T&, const T&), const T& number) override
    {
        T temp_elem;
        ArraySequenceImmut<T>* new_sequence = new ArraySequenceImmut<T>(this->array.GetArray(), this->GetLength());
        for (int ii = 0; ii < new_sequence->GetLength(); ii++)
        {
            temp_elem = func(new_sequence->Get(ii), number);
            new_sequence->array.Set(temp_elem, ii);
        }
        return new_sequence;
    }

    const T& Reduce(T(*func) (const T&, const T&), const T& starting_value) override
    {
        T result = starting_value;
        for (int ii = 0; ii < this->GetLength(); ii++)
        {
            result = func(result, this->Get(ii));
        }
        return result;
    }

    Sequence<T>* Where(bool(*func) (const T&)) override
    {
        DynamicArray<T> yarray = this->array;
        int capacity = this->array.GetCapacity();
        int length = 0;
        T* passed_elems = new T[capacity];
        for (int ii = 0; ii < this->GetLength(); ii++)
        {
            if (func(this->Get(ii)) == true)
            {
                passed_elems[length] = this->Get(ii);
                length++;
            }
        }
        ArraySequenceImmut<T>* new_sequence = new ArraySequenceImmut<T>(passed_elems, length, capacity);
        return new_sequence;
    }

    ArraySequenceImmut<T> operator +(const T& item)
    {
        ArraySequenceImmut<T>* new_sequence = new ArraySequenceImmut<T>(this->array.GetArray(), this->GetLength());
        int capacity = array.GetCapacity();
        int length = array.GetLength() + 1;
        if (length > capacity)
        {
            if (capacity < 1000)
            {
                new_sequence->array.Resize(2 * capacity);
            }
            else
            {
                new_sequence->array.Resize(capacity + 1000);
            }
        }
        new_sequence->array.Set(item, length - 1);
        return *new_sequence;
    }

    ArraySequenceImmut<T> operator +(Sequence<T>* OtherSeq)
    {
        ArraySequenceImmut<T>* new_sequence = new ArraySequenceImmut<T>(this->array->GetArray(), this->GetLength());
        int length1 = new_sequence->GetLength();
        int length2 = OtherSeq->GetLength();
        if (length1 + length2 > new_sequence->array->GetCapacity())
        {
            new_sequence->array->Resize(length1 + length2);
        }
        for (int ii = length1; ii < (length1 + length2); ii++)
        {
            new_sequence->array->Set(OtherSeq->Get(ii - length1), ii);
        }
        return *new_sequence;
    }
};

template <class T>
class ArraySequenceMut : public ArraySequenceImmut<T>
{
public:
    ArraySequenceMut(T* items, int count) : ArraySequenceImmut<T>(items, count) { }

    ArraySequenceMut(int size) : ArraySequenceImmut<T>(size) { }

    ArraySequenceMut() : ArraySequenceImmut<T>() { }

    ArraySequenceMut(const DynamicArray<T>& dynamic_array) : ArraySequenceImmut<T>(dynamic_array) { }

    ArraySequenceMut(const ArraySequenceMut<T>& other_seq) : ArraySequenceImmut<T>(other_seq) { }

    ArraySequenceMut(ArraySequenceMut<T>&& other_seq) : ArraySequenceImmut<T>(other_seq) { }

    ArraySequenceMut(Sequence<T>* other_seq) : ArraySequenceImmut<T>(other_seq) { }

    ArraySequenceMut& operator = (const ArraySequenceMut<T>& other_seq)
    {
        this->array = DynamicArray<T>(other_seq.array);
        return *this;
    }

    Sequence<T>* Set(const T& item, int index) override
    {
        this->array.Set(item, index);
        ArraySequenceMut<T>* new_sequence = new ArraySequenceMut<T>(this->array.GetArray(), this->GetLength());
        return new_sequence;
    }

    Sequence<T>* SetSubsequence(Sequence<T>* subsequence, int index) override
    {
        for (int ii = 0; ii = subsequence->GetLength(); ii++)
        {
            this->Set(subsequence->Get(ii), ii + index);
        }
        ArraySequenceImmut<T>* new_sequence = new ArraySequenceImmut<T>(this->array.GetArray(), this->GetLength());
        return new_sequence;
    }

    Sequence<T>* Append(const T& item) override
    {
        int capacity = this->array.GetCapacity();
        int length = this->array.GetLength() + 1;
        if (length > capacity)
        {
            if (capacity < 1000)
            {
                this->array.Resize(2 * capacity);
            }
            else
            {
                this->array.Resize(capacity + 1000);
            }
        }
        this->Set(item, length - 1);
        ArraySequenceMut<T>* new_sequence = new ArraySequenceMut<T>(this->array.GetArray(), this->GetLength());
        return new_sequence;
    }

    Sequence<T>* Prepend(const T& item) override
    {
        int capacity = this->array.GetCapacity();
        int length = this->array.GetLength() + 1;
        if (length > capacity)
        {
            if (capacity < 1000)
            {
                this->array.Resize(2 * capacity);
            }
            else
            {
                this->array.Resize(capacity + 1000);
            }
        }
        for (int ii = length - 2; ii >= 0; ii--)
        {
            this->array.Set(this->Get(ii), ii + 1);
        }
        this->array.Set(item, 0);
        ArraySequenceMut<T>* new_sequence = new ArraySequenceMut<T>(this->array.GetArray(), this->GetLength());
        return new_sequence;
    }

    Sequence<T>* Concatenate(Sequence<T>* OtherSeq) override
    {
        int length1 = this->GetLength();
        int length2 = OtherSeq->GetLength();
        if (length1 + length2 > this->array.GetCapacity())
        {
            this->array.Resize(length1 + length2);
        }
        for (int ii = length1; ii < (length1 + length2); ii++)
        {
            this->Set(OtherSeq->Get(ii - length1), ii);
        }
        ArraySequenceMut<T>* new_sequence = new ArraySequenceMut<T>(this->array.GetArray(), this->GetLength());
        return new_sequence;
    }

    Sequence<T>* InsertAt(const T& item, int index) override
    {
        int capacity = this->array.GetCapacity();
        int length = this->array.GetLength() + 1;
        if (length > capacity)
        {
            if (capacity < 1000)
            {
                this->array.Resize(2 * capacity);
            }
            else
            {
                this->array.Resize(capacity + 1000);
            }
        }
        for (int ii = length - 2; ii >= index; ii--)
        {
            this->array.Set(this->Get(ii), ii + 1);
        }
        this->array.Set(item, index);
        ArraySequenceMut<T>* new_sequence = new ArraySequenceMut<T>(this->array.GetArray(), this->GetLength());
        return new_sequence;
    }

    Sequence<T>* Map(T(*func) (const T&, const T&), const T& number) override
    {
        T temp_elem;
        for (int ii = 0; ii < this->GetLength(); ii++)
        {
            temp_elem = func(this->Get(ii), number);
            this->Set(temp_elem, ii);
        }
        ArraySequenceMut<T>* new_sequence = new ArraySequenceMut<T>(this->array.GetArray(), this->GetLength());
        return new_sequence;
    }
};

#endif