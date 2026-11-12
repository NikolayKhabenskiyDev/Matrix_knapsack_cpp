#ifndef PAIR_H
#define PAIR_H

#include<string>
#include "Node.h"
#include "BinSearchTree.h"

template<class T1, class T2>
class Pair
{
private:
	T1 key = T1();
	T2 data = T2();

public:
	Pair(const T1& key_item, const T2& data_item)
	{
		key = T1(key_item);
		data = T2(data_item);
	}

	Pair()
	{
		key = T1();
		data = T2();
	}

	Pair(const Pair<T1, T2>& other_pair)
	{
		key = T1(other_pair.key);
		data = T2(other_pair.data);
	}

	Pair(Pair<T1, T2>* other_pair)
	{
		key = T1(other_pair->key);
		data = T2(other_pair->data);
	}

	Pair(Pair<T1, T2>&& other_pair)
	{
		key = other_pair.key;
		data = other_pair.data;
		other_pair.key = T1();
		other_pair.data = T2();
	}

	Pair& operator = (const Pair<T1, T2>& other_pair)
	{
		key = T1(other_pair.key);
		data = T2(other_pair.data);
		return *this;
	}

	Pair& operator = (Pair<T1, T2>&& other_pair)
	{
		key = other_pair.key;
		data = other_pair.data;
		other_pair.key = T1();
		other_pair.data = T2();
		return *this;
	}

	T1 GetKey() const
	{
		return key;
	}

	T2 GetData() const
	{
		return data;
	}

	void SetKey(const T1& new_key)
	{
		key = new_key;
	}

	void SetData(const T2& new_data)
	{
		data = new_data;
	}

	friend bool operator ==(const Pair<T1, T2>& term1, const Pair<T1, T2>& term2);
};

template <class T1, class T2>
bool operator ==(const Pair<T1, T2>& pair1, const Pair<T1, T2>& pair2)
{
	if (pair1.key == pair2.key)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

template <class T1, class T2>
std::ostream& operator << (std::ostream& stream, const Pair<T1, T2>& pair)
{
	stream << pair.GetKey() << ": " << pair.GetData() << " ";
	return stream;
}

template <class T1, class T2>
std::ostream& operator << (std::ostream& stream, Pair<T1, T2>* pair)
{
	stream << pair->GetKey() << ": " << pair->GetData() << " ";
	return stream;
}

std::ostream& operator << (std::ostream& stream, const Pair<int, int>& pair)
{
	stream << pair.GetKey() << ", " << pair.GetData() << " ";
	return stream;
}

std::ostream& operator << (std::ostream& stream, Pair<int, int>* pair)
{
	stream << pair->GetKey() << ", " << pair->GetData() << " ";
	return stream;
}

template<class T1, class T2>
class DynamicPair
{
private:
	T1* key;
	T2* data;

public:
	DynamicPair(const T1& key_item, const T2& data_item)
	{
		key = new T1(key_item);
		data = new T2(data_item);
	}

	DynamicPair(T1* key_item, T2* data_item)
	{
		key = new T1(key_item);
		data = new T2(data_item);
	}

	DynamicPair()
	{
		key = new T1();
		data = new T2();
	}

	DynamicPair(const DynamicPair<T1, T2>& other_pair)
	{
		key = new T1(*other_pair.key);
		data = new T2(*other_pair.data);
	}

	DynamicPair(DynamicPair<T1, T2>* other_pair)
	{
		key = new T1(*other_pair->key);
		data = new T2(*other_pair->data);
	}

	DynamicPair(DynamicPair<T1, T2>&& other_pair)
	{
		key = other_pair.key;
		data = other_pair.data;
		other_pair.key = nullptr;
		other_pair.data = nullptr;
	}

	DynamicPair& operator = (const DynamicPair<T1, T2>& other_pair)
	{
		if (key != nullptr)
		{
			delete key;
		}
		if (data != nullptr)
		{
			delete data;
		}
		key = new T1(*other_pair.key);
		data = new T2(*other_pair.data);
		return *this;
	}

	DynamicPair& operator = (DynamicPair<T1, T2>* other_pair)
	{
		if (key != nullptr)
		{
			delete key;
		}
		if (data != nullptr)
		{
			delete data;
		}
		std::cout << T1(*other_pair->key);
		key = new T1(*other_pair->key);
		data = new T2(*other_pair->data);
		return *this;
	}

	DynamicPair& operator = (DynamicPair<T1, T2>&& other_pair)
	{
		key = other_pair.key;
		data = other_pair.data;
		other_pair.key = nullptr;
		other_pair.data = nullptr;
		return *this;
	}

	T1* GetKey() const
	{
		return key;
	}

	T2* GetData() const
	{
		return data;
	}

	void SetKey(T1* new_key)
	{
		if (key != nullptr)
		{
			delete key;
		}
		key = new_key;
	}

	void SetData(T2* new_data)
	{
		if (data != nullptr)
		{
			delete data;
		}
		data = new_data;
	}

	~DynamicPair()
	{
		if (key != nullptr)
		{
			delete key;
		}
		if (data != nullptr)
		{
			delete data;
		}
	}

	friend bool operator ==(const DynamicPair<T1, T2>& term1, const DynamicPair<T1, T2>& term2);
};

template <class T1, class T2>
bool operator ==(const DynamicPair<T1, T2>& pair1, const DynamicPair<T1, T2>& pair2)
{
	if (*pair1.key == *pair2.key)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

template <class T1, class T2>
std::ostream& operator << (std::ostream& stream, const DynamicPair<T1, T2>& pair)
{
	stream << *pair.GetKey() << ": " << *pair.GetData() << " ";
	return stream;
}

template <class T1, class T2>
std::ostream& operator << (std::ostream& stream, DynamicPair<T1, T2>* pair)
{
	stream << *pair->GetKey() << ": " << *pair->GetData() << " ";
	return stream;
}

#endif