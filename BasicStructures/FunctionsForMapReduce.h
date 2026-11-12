#ifndef FUNCTIONSFORMAPREDUCE_H
#define FUNCTIONSFORMAPREDUCE_H

template <class T>
T Add(const T& elem, const T& operand)
{
    T result;
    result = elem + operand;
    return result;
}

template <class T>
T Multiply(const T& elem, const T& operand)
{
    T result;
    result = elem * operand;
    return result;
}

template <class T>
bool Where_IsOdd(const T& elem)
{
    int elem_int;
    elem_int = elem;
    if (elem_int % 2 == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

template <class T>
bool Where_IsEven(const T& elem)
{
    int elem_int;
    elem_int = elem;
    if (elem_int % 2 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
template <class T>
bool Where_IsBiggerThan100(const T& elem)
{
    int elem_int;
    elem_int = elem;
    if (elem_int > 100)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

#endif