#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>

template <class T>
class Sequence
{
public:
    virtual ~Sequence() {};

    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual int GetLength() const = 0;
    virtual Sequence<T>* Set(const T& item, int index) = 0;
    virtual Sequence<T>* GetSubsequence(int start_index, int end_index) = 0;
    virtual Sequence<T>* SetSubsequence(Sequence<T>* subsequence, int index) = 0;

    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* InsertAt(const T& item, int index) = 0;

    virtual Sequence<T>* Concatenate(Sequence<T>* OtherSeq) = 0;

    virtual Sequence<T>* Map(T(*func) (const T&, const T&), const T& number) = 0;
    virtual const T& Reduce(T(*func) (const T&, const T&), const T& starting_value) = 0;
    virtual Sequence<T>* Where(bool(*func) (const T&)) = 0;
};

template <class T>
std::ostream& operator << (std::ostream& stream, Sequence<T>* seq)
{
    for (int ii = 0; ii < seq->GetLength(); ii++)
    {
        stream << " " << seq->Get(ii);
    }
    return stream;
}

template <class T>
std::ostream& operator << (std::ostream& stream, const Sequence<T>& seq)
{
    for (int ii = 0; ii < seq.GetLength(); ii++)
    {
        stream << " " << seq.Get(ii);
    }
    return stream;
}

#endif
