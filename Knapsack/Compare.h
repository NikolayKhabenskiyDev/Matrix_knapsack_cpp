#ifndef COMPARE_H
#define COMPARE_H

#include<string>
#include "Trees/DictionaryTree.h"
#include "Knapsack.h"

bool More(std::string item1, std::string item2)
{
	int min_len = item1.length();
	bool longer = 0;
	if (min_len > item2.length())
	{
		min_len = item2.length();
		longer = 1;
	}
	for (int ii = 0; ii < min_len; ii++)
	{
		if (item1[ii] > item2[ii])
		{
			return 1;
		}
	}
	if (longer == 0)
	{
		if (item2[min_len] == '1')
		{
			return 0;
		}
		if (item2[min_len] == '0')
		{
			return 1;
		}
	}
	else
	{
		if (item1[min_len] == '1')
		{
			return 1;
		}
		if (item1[min_len] == '0')
		{
			return 0;
		}
	}
}

bool Less(std::string item1, std::string item2)
{
	if (item1.length() < item2.length())
	{
		for (int ii = 0; ii < item1.length(); ii++)
		{
			if (item1[ii] > item2[ii])
			{
				return 0;
			}
		}
		if (item2[item1.length()] == '1')
		{
			return 1;
		}
		if (item2[item1.length()] == '0')
		{
			return 0;
		}
	}
	else
	{
		for (int ii = 0; ii < item2.length(); ii++)
		{
			if (item1[ii] > item2[ii])
			{
				return 0;
			}
		}
		if (item1[item2.length()] == '1')
		{
			return 0;
		}
		if (item1[item2.length()] == '0')
		{
			return 1;
		}
	}
}

bool More(const int& item1, const int& item2)
{
	if (item1 > item2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool Less(const int& item1, const int& item2)
{
	if (item1 < item2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool More(const float& item1, const float& item2)
{
	if (item1 > item2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool Less(const float& item1, const float& item2)
{
	if (item1 < item2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool More(const Pair<std::string, KnapsackContent>& item1, const Pair<std::string, KnapsackContent>& item2)
{
	return More(item1.GetKey(), item2.GetKey());
}

bool Less(const Pair<std::string, KnapsackContent>& item1, const Pair<std::string, KnapsackContent>& item2)
{
	return Less(item1.GetKey(), item2.GetKey());
}

bool More(Pair<int, int> item1, Pair<int, int> item2)
{
	if (item1.GetKey() < item2.GetKey())
	{
		return 1;
	}
	if (item1.GetData() < item2.GetData())
	{
		return 1;
	}
	return 0;
}

bool Less(Pair<int, int> item1, Pair<int, int> item2)
{
	if (item1.GetKey() < item2.GetKey())
	{
		return 1;
	}
	if (item1.GetData() < item2.GetData())
	{
		return 1;
	}
	return 0;
}

bool More(const ArraySequenceMut<Pair<int, int>>& item1, const ArraySequenceMut<Pair<int, int>>& item2)
{
	if (item1.GetLength() < item2.GetLength())
	{
		for (int ii = 0; ii < item1.GetLength(); ii++)
		{
			if (item1.Get(ii).GetKey() > item2.Get(ii).GetKey())
			{
				return 1;
			}
			if (item1.Get(ii).GetKey() < item2.Get(ii).GetKey())
			{
				return 0;
			}
			if (item1.Get(ii).GetData() > item2.Get(ii).GetData())
			{
				return 1;
			}
		}
		return 0;
	}
	else
	{
		for (int ii = 0; ii < item2.GetLength(); ii++)
		{
			if (item1.Get(ii).GetKey() < item2.Get(ii).GetKey())
			{
				return 0;
			}
			if (item1.Get(ii).GetKey() > item2.Get(ii).GetKey())
			{
				return 1;
			}
			if (item1.Get(ii).GetData() < item2.Get(ii).GetData())
			{
				return 0;
			}
		}
		return 1;
	}
}

bool Less(const ArraySequenceMut<Pair<int, int>>& item1, const ArraySequenceMut<Pair<int, int>>& item2)
{
	if (item1.GetLength() < item2.GetLength())
	{
		for (int ii = 0; ii < item1.GetLength(); ii++)
		{
			if (item1.Get(ii).GetKey() > item2.Get(ii).GetKey())
			{
				return 0;
			}
			if (item1.Get(ii).GetKey() < item2.Get(ii).GetKey())
			{
				return 1;
			}
			if (item1.Get(ii).GetData() > item2.Get(ii).GetData())
			{
				return 0;
			}
		}
		return 1;
	}
	else
	{
		for (int ii = 0; ii < item2.GetLength(); ii++)
		{
			if (item1.Get(ii).GetKey() < item2.Get(ii).GetKey())
			{
				return 1;
			}
			if (item1.Get(ii).GetKey() > item2.Get(ii).GetKey())
			{
				return 0;
			}
			if (item1.Get(ii).GetData() < item2.Get(ii).GetData())
			{
				return 1;
			}
		}
		return 0;
	}
}

bool More(const Pair<ArraySequenceMut<Pair<int, int>>, MatrKnapContent>& item1,
	const Pair<ArraySequenceMut<Pair<int, int>>, MatrKnapContent>& item2)
{
	return More(item1.GetKey(), item2.GetKey());
}

bool Less(const Pair<ArraySequenceMut<Pair<int, int>>, MatrKnapContent>& item1,
	const Pair<ArraySequenceMut<Pair<int, int>>, MatrKnapContent>& item2)
{
	return Less(item1.GetKey(), item2.GetKey());
}

bool More(const DynamicPair<ArraySequenceMut<Pair<int, int>>, MatrKnapContent>& item1,
	const DynamicPair<ArraySequenceMut<Pair<int, int>>, MatrKnapContent>& item2)
{
	return More(item1.GetKey(), item2.GetKey());
}

bool Less(const DynamicPair<ArraySequenceMut<Pair<int, int>>, MatrKnapContent>& item1,
	const DynamicPair<ArraySequenceMut<Pair<int, int>>, MatrKnapContent>& item2)
{
	return Less(item1.GetKey(), item2.GetKey());
}

bool More(Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>* item1,
	Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>* item2)
{
	return More(item1->GetKey(), item2->GetKey());
}

bool Less(Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>* item1,
	Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>* item2)
{
	return Less(item1->GetKey(), item2->GetKey());
}

#endif