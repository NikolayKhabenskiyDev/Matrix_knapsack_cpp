#ifndef KNAPSACK_H
#define KNAPSACK_H

#include<string>
#include <iostream>
#include <iomanip>

class KnapsackItem
{
public:
	std::string name;
	int weight;
	int value;

	KnapsackItem()
	{
		name = "";
		weight = 0;
		value = 0;
	}

	KnapsackItem(std::string new_name, int new_weight, int new_price)
	{
		name = new_name;
		weight = new_weight;
		value = new_price;
	}

	KnapsackItem(const KnapsackItem& other_knap)
	{
		name = other_knap.name;
		weight = other_knap.weight;
		value = other_knap.value;
	}

	KnapsackItem& operator = (const KnapsackItem& other_knap)
	{
		name = other_knap.name;
		weight = other_knap.weight;
		value = other_knap.value;
		return *this;
	}
};

class KnapsackContent
{
protected:
	KnapsackItem* items;
	int sum_weight;
	int sum_value;
	int amount;
	int max_weight;

public:
	KnapsackContent()
	{
		items = new KnapsackItem[1];
		sum_weight = 0;
		sum_value = 0;
		amount = 0;
		max_weight = 0;
	}

	KnapsackContent(int limit_weight)
	{
		items = new KnapsackItem[1];
		sum_weight = 0;
		sum_value = 0;
		amount = 0;
		max_weight = limit_weight;
	}

	KnapsackContent(KnapsackItem* new_items, int length, int limit_weight)
	{
		items = new_items;
		max_weight = limit_weight;
		sum_weight = 0;
		sum_value = 0;
		amount = 0;
		for (int ii = 0; ii < length; ii++)
		{
			sum_weight = sum_weight + items[ii].weight;
			sum_value = sum_value + items[ii].value;
			amount++;
		}
	}

	KnapsackContent(const KnapsackContent& other_knapsack)
	{
		KnapsackItem* new_content = new KnapsackItem[other_knapsack.amount];
		sum_weight = other_knapsack.sum_weight;
		sum_value = other_knapsack.sum_value;
		amount = other_knapsack.amount;
		max_weight = other_knapsack.max_weight;
		for (int ii = 0; ii < other_knapsack.amount; ii++)
		{
			new_content[ii] = other_knapsack.items[ii];
		}
		items = new_content;
	}

	KnapsackContent(KnapsackContent* other_knapsack)
	{
		KnapsackItem* new_content = new KnapsackItem[other_knapsack->amount];
		sum_weight = other_knapsack->sum_weight;
		sum_value = other_knapsack->sum_value;
		amount = other_knapsack->amount;
		max_weight = other_knapsack->max_weight;
		for (int ii = 0; ii < other_knapsack->amount; ii++)
		{
			new_content[ii] = other_knapsack->items[ii];
		}
		items = new_content;
	}

	KnapsackContent(KnapsackContent&& other_knapsack)
	{
		items = other_knapsack.items;
		sum_weight = other_knapsack.sum_weight;
		sum_value = other_knapsack.sum_value;
		amount = other_knapsack.amount;
		max_weight = other_knapsack.max_weight;
		other_knapsack.items = nullptr;
		other_knapsack.sum_weight = 0;
		other_knapsack.sum_value = 0;
		other_knapsack.amount = 0;
		other_knapsack.max_weight = 0;
	}

	KnapsackContent& operator = (const KnapsackContent& other_knapsack)
	{
		delete[] items;
		KnapsackItem* new_content = new KnapsackItem[other_knapsack.amount];
		sum_weight = other_knapsack.sum_weight;
		sum_value = other_knapsack.sum_value;
		amount = other_knapsack.amount;
		max_weight = other_knapsack.max_weight;
		for (int ii = 0; ii < other_knapsack.amount; ii++)
		{
			new_content[ii] = other_knapsack.items[ii];
		}
		items = new_content;
		return *this;
	}

	KnapsackContent& operator = (KnapsackContent* other_knapsack)
	{
		delete[] items;
		KnapsackItem* new_content = new KnapsackItem[other_knapsack->amount];
		sum_weight = other_knapsack->sum_weight;
		sum_value = other_knapsack->sum_value;
		amount = other_knapsack->amount;
		max_weight = other_knapsack->max_weight;
		for (int ii = 0; ii < other_knapsack->amount; ii++)
		{
			new_content[ii] = other_knapsack->items[ii];
		}
		items = new_content;
		return *this;
	}

	KnapsackContent operator = (KnapsackContent&& other_knapsack)
	{
		delete[] items;
		items = other_knapsack.items;
		sum_weight = other_knapsack.sum_weight;
		sum_value = other_knapsack.sum_value;
		amount = other_knapsack.amount;
		max_weight = other_knapsack.max_weight;
		other_knapsack.items = nullptr;
		other_knapsack.sum_weight = 0;
		other_knapsack.sum_value = 0;
		other_knapsack.amount = 0;
		other_knapsack.max_weight = 0;
		return this;
	}

	~KnapsackContent()
	{
		if (items != nullptr)
		{
			delete[] items;
			items = nullptr;
		}
	}

	KnapsackItem GetItem(int index) const
	{
		return items[index];
	}

	int GetWeight() const
	{
		return sum_weight;
	}

	int GetValue() const
	{
		return sum_value;
	}

	int GetAmount() const
	{
		return amount;
	}

	int GetMaxWeight() const
	{
		return max_weight;
	}

	KnapsackContent* AddElem(KnapsackItem new_item)
	{
		KnapsackItem* new_content = new KnapsackItem[amount + 1];
		for (int ii = 0; ii < amount; ii++)
		{
			new_content[ii] = items[ii];
		}
		new_content[amount] = new_item;
		delete[] items;
		items = new_content;
		sum_weight = sum_weight + new_item.weight;
		sum_value = sum_value + new_item.value;
		amount++;
		return this;
	}
};

std::ostream& operator << (std::ostream& stream, const KnapsackItem& item)
{
	stream << item.name;
	return stream;
}

std::ostream& operator << (std::ostream& stream, KnapsackItem* item)
{
	stream << item->name;
	return stream;
}

std::ostream& operator << (std::ostream& stream, const KnapsackContent& knap)
{
	if (knap.GetAmount() > 0)
	{
		for (int ii = 0; ii < knap.GetAmount() - 1; ii++)
		{
			stream << knap.GetItem(ii) << ", ";
		}
		stream << knap.GetItem(knap.GetAmount() - 1);
	}
	return stream;
}

std::ostream& operator << (std::ostream& stream, KnapsackContent* knap)
{
	if (knap->GetAmount() > 0)
	{
		for (int ii = 0; ii < knap->GetAmount() - 1; ii++)
		{
			stream << knap->GetItem(ii) << ", ";
		}
		stream << knap->GetItem(knap->GetAmount() - 1);
	}
	return stream;
}

bool operator == (const KnapsackItem& item1, const KnapsackItem& item2)
{
	if (item1.name != item2.name)
	{
		return 0;
	}
	if (item1.weight != item2.weight)
	{
		return 0;
	}
	if (item1.value != item2.value)
	{
		return 0;
	}
	return 1;
}

bool operator != (const KnapsackItem& item1, const KnapsackItem& item2)
{
	if (item1.name != item2.name)
	{
		return 1;
	}
	if (item1.weight != item2.weight)
	{
		return 1;
	}
	if (item1.value != item2.value)
	{
		return 1;
	}
	return 0;
}

bool operator == (const KnapsackContent& cont1, const KnapsackContent& cont2)
{
	if (cont1.GetAmount() != cont2.GetAmount())
	{
		return 0;
	}
	for (int ii = 0; ii < cont1.GetAmount(); ii++)
	{
		if (cont1.GetItem(ii) != cont2.GetItem(ii))
		{
			return 0;
		}
	}
	if (cont1.GetMaxWeight() != cont2.GetMaxWeight())
	{
		return 0;
	}
	return 1;
}

bool operator != (const KnapsackContent& cont1, const KnapsackContent& cont2)
{
	if (cont1.GetAmount() != cont2.GetAmount())
	{
		return 1;
	}
	for (int ii = 0; ii < cont1.GetAmount(); ii++)
	{
		if (cont1.GetItem(ii) != cont2.GetItem(ii))
		{
			return 1;
		}
	}
	if (cont1.GetMaxWeight())
	{
		return 1;
	}
	return 0;
}

#endif
