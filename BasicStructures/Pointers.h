#ifndef POINTERS_H
#define POINTERS_H

template<class T>
class unique_ptr
{
private:
    T* data;

public:

    unique_ptr()
    {
        data = nullptr;
    }

    unique_ptr(T* new_data)
    {
        data = new_data;
    }

    unique_ptr(T new_data)
    {
        data = &new_data;
    }

    unique_ptr(const unique_ptr& ptr) = delete;

    void operator=(const unique_ptr& ptr) = delete;

    unique_ptr(unique_ptr&& ptr)
    {
        this->data = ptr.data;
        ptr.data = nullptr;
    }

    void operator=(unique_ptr&& ptr)
    {
        this->data = ptr.data;
        ptr.data = nullptr;
    }

    operator T* ()
    {
        return data;
    }

    T operator [] (int index)
    {
        return data[index];
    }

    T* operator->()
    {
        return data;
    }

    T Get()
    {
        return *data;
    }

    ~unique_ptr()
    {
        if (data != nullptr)
        {
            delete data;
            data = nullptr;
        }
    }
};

template<class T>
class smart_ptr
{
private:
    T* data;
    int* count;

public:
    smart_ptr()
    {
        data = nullptr;
        count = new int(0);
    }

    smart_ptr(T* new_data)
    {
        data = new_data;
        count = new int(1);
    }

    smart_ptr(const smart_ptr<T>& ptr)
    {
        this->data = ptr.data;
        this->count = ptr.count;
        (*count)++;
    }

    void operator=(const smart_ptr<T>& ptr)
    {
        this->data = ptr.data;
        this->count = ptr.count;
        (*count)++;
    }

    smart_ptr(smart_ptr<T>&& ptr)
    {
        this->data = ptr.data;
        ptr.data = nullptr;
    }

    void operator=(smart_ptr<T>&& ptr)
    {
        this->data = ptr.data;
        ptr.data = nullptr;
    }

    operator T* ()
    {
        return data;
    }

    T* operator->()
    {
        return data;
    }

    T Get()
    {
        return *data;
    }

    ~smart_ptr()
    {
        (*count)--;
        if (*count < 1 && data != nullptr)
        {
            delete data;
            delete count;
            data = nullptr;
        }
    }
};

#endif