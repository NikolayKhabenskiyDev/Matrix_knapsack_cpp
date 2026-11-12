#ifndef MATRKNAP_H
#define MATRKNAP_H

#include<string>
#include <iostream>
#include <iomanip>
#include "Matriñes/RectangleMatrix.h"
#include "Matriñes/MatrixFunctions.h"
#include "Knapsack.h"

class MatrKnapItem : public KnapsackItem
{
public:
	RectangleMatrix<int>* matr = new RectangleMatrix<int>();

	MatrKnapItem() : KnapsackItem()
	{
		this->matr = new RectangleMatrix<int>();
	}

	MatrKnapItem(std::string new_name, int new_weight, int new_price, RectangleMatrix<int>* new_matr) :
		KnapsackItem(new_name, new_weight, new_price)
	{
		this->matr = new RectangleMatrix<int>(new_matr);
	}

	MatrKnapItem(const MatrKnapItem& other_knap)
	{
		this->name = other_knap.name;
		this->weight = other_knap.weight;
		this->value = other_knap.value;
		this->matr = new RectangleMatrix<int>(other_knap.matr);
	}

	MatrKnapItem& operator = (const MatrKnapItem& other_knap)
	{
		this->name = other_knap.name;
		this->weight = other_knap.weight;
		this->value = other_knap.value;
		this->matr = new RectangleMatrix<int>(other_knap.matr);
		return *this;
	}

	~MatrKnapItem()
	{
		if (this->matr != nullptr)
		{
			delete this->matr;
		}
	}

	RectangleMatrix<int>* GetMatr() const
	{
		return this->matr;
	}
};

class MatrKnapContent : public KnapsackContent
{
protected:
	MatrKnapItem** volume_items = nullptr;
	RectangleMatrix<int>* knapsack_space = new RectangleMatrix<int>();

public:
	MatrKnapContent() : KnapsackContent()
	{
		this->volume_items = nullptr;
		this->knapsack_space = new RectangleMatrix<int>();
	}

	MatrKnapContent(int limit_weight, int height, int width) : KnapsackContent(limit_weight)
	{
		this->volume_items = nullptr;
		this->knapsack_space = new RectangleMatrix<int>(height, width);
	}

	MatrKnapContent(const MatrKnapContent& other_knapsack)
	{
		MatrKnapItem** new_content = new MatrKnapItem*[other_knapsack.amount + 1];
		this->sum_weight = other_knapsack.sum_weight;
		this->sum_value = other_knapsack.sum_value;
		this->amount = other_knapsack.amount;
		this->max_weight = other_knapsack.max_weight;
		for (int ii = 0; ii < other_knapsack.amount; ii++)
		{
			new_content[ii] = other_knapsack.volume_items[ii];
		}
		this->volume_items = new_content;
		if (other_knapsack.knapsack_space != nullptr)
		{
			this->knapsack_space = new RectangleMatrix<int>(other_knapsack.knapsack_space);
		}
		else
		{
			this->knapsack_space = nullptr;
		}
	}

	MatrKnapContent(MatrKnapContent* other_knapsack)
	{
		MatrKnapItem** new_content = new MatrKnapItem * [other_knapsack->amount + 1];
		this->sum_weight = other_knapsack->sum_weight;
		this->sum_value = other_knapsack->sum_value;
		this->amount = other_knapsack->amount;
		this->max_weight = other_knapsack->max_weight;
		for (int ii = 0; ii < other_knapsack->amount; ii++)
		{
			new_content[ii] = other_knapsack->volume_items[ii];
		}
		this->volume_items = new_content;
		this->knapsack_space = new RectangleMatrix<int>(other_knapsack->knapsack_space);
	}

	MatrKnapContent(MatrKnapContent&& other_knapsack)
	{
		this->volume_items = other_knapsack.volume_items;
		this->sum_weight = other_knapsack.sum_weight;
		this->sum_value = other_knapsack.sum_value;
		this->amount = other_knapsack.amount;
		this->max_weight = other_knapsack.max_weight;
		this->knapsack_space = other_knapsack.knapsack_space;
		other_knapsack.volume_items = nullptr;
		other_knapsack.sum_weight = 0;
		other_knapsack.sum_value = 0;
		other_knapsack.amount = 0;
		other_knapsack.max_weight = 0;
		other_knapsack.knapsack_space = nullptr;
	}

	MatrKnapContent& operator = (MatrKnapContent* other_knapsack)
	{
		if (this->volume_items != nullptr)
		{
			delete[] this->volume_items;
		}
		if (this->knapsack_space != nullptr)
		{
			delete this->knapsack_space;
		}
		MatrKnapItem** new_content = new MatrKnapItem * [other_knapsack->amount + 1];
		this->sum_weight = other_knapsack->sum_weight;
		this->sum_value = other_knapsack->sum_value;
		this->amount = other_knapsack->amount;
		this->max_weight = other_knapsack->max_weight;
		for (int ii = 0; ii < other_knapsack->amount; ii++)
		{
			new_content[ii] = other_knapsack->volume_items[ii];
		}
		this->volume_items = new_content;
		this->knapsack_space = new RectangleMatrix<int>(other_knapsack->knapsack_space);
		return *this;

	}

	MatrKnapContent& operator= (const MatrKnapContent& other_knapsack)
	{
		if (volume_items != nullptr)
		{
			delete[] volume_items;
		}
		if (knapsack_space != nullptr)
		{
			delete knapsack_space;
		}
		MatrKnapItem** new_content = new MatrKnapItem*[other_knapsack.amount + 1];
		this->sum_weight = other_knapsack.sum_weight;
		this->sum_value = other_knapsack.sum_value;
		this->amount = other_knapsack.amount;
		this->max_weight = other_knapsack.max_weight;
		for (int ii = 0; ii < other_knapsack.amount; ii++)
		{
			new_content[ii] = other_knapsack.volume_items[ii];
		}
		this->volume_items = new_content;
		this->knapsack_space = new RectangleMatrix<int>(other_knapsack.knapsack_space);
		return *this;
	}

	MatrKnapContent& operator = (MatrKnapContent&& other_knapsack)
	{
		if (volume_items != nullptr)
		{
			delete[] volume_items;
		}
		if (knapsack_space != nullptr)
		{
			delete knapsack_space;
		}
		this->volume_items = other_knapsack.volume_items;
		this->sum_weight = other_knapsack.sum_weight;
		this->sum_value = other_knapsack.sum_value;
		this->amount = other_knapsack.amount;
		this->max_weight = other_knapsack.max_weight;
		this->knapsack_space = other_knapsack.knapsack_space;
		other_knapsack.volume_items = nullptr;
		other_knapsack.sum_weight = 0;
		other_knapsack.sum_value = 0;
		other_knapsack.amount = 0;
		other_knapsack.max_weight = 0;
		other_knapsack.knapsack_space = nullptr;
		return *this;
	}

	~MatrKnapContent()
	{
		if (this->volume_items != nullptr)
		{
			delete this->volume_items;
			this->volume_items = nullptr;
		}
		if (this->knapsack_space != nullptr)
		{
			delete this->knapsack_space;
			this->knapsack_space = nullptr;
		}
	}

	MatrKnapItem* GetItem(int index) const
	{
		return this->volume_items[index];
	}

	RectangleMatrix<int>* GetMatr() const
	{
		return this->knapsack_space;
	}

	MatrKnapContent* AddElem(MatrKnapItem* new_item, int corner_row_index, int corner_col_index)
	{
		MatrKnapItem** new_content = new MatrKnapItem*[this->amount + 1];
		for (int ii = 0; ii < this->amount; ii++)
		{
			new_content[ii] = this->volume_items[ii];
		}
		new_content[this->amount] = new_item;
		delete[] this->volume_items;
		this->volume_items = new_content;
		this->sum_weight = this->sum_weight + new_item->weight;
		this->sum_value = this->sum_value + new_item->value;
		this->amount++;
		this->knapsack_space = AddSubMatrix(this->knapsack_space, new_item->matr, corner_row_index, corner_col_index);
		return this;
	}
};

bool operator == (const MatrKnapItem& item1, const MatrKnapItem& item2)
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
	if (item1.matr != item2.matr)
	{
		return 0;
	}
	return 1;
}

bool operator != (const MatrKnapItem& item1, const MatrKnapItem& item2)
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
	if (item1.matr != item2.matr)
	{
		return 1;
	}
	return 0;
}

bool operator == (const MatrKnapContent& cont1, const MatrKnapContent& cont2)
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
	if (*(cont1.GetMatr()) != *(cont2.GetMatr()))
	{
		return 0;
	}
	return 1;
}

bool operator != (const MatrKnapContent& cont1, const MatrKnapContent& cont2)
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
	if (cont1.GetMaxWeight() != cont2.GetMaxWeight())
	{
		return 1;
	}
	if (cont1.GetMatr() != cont2.GetMatr())
	{
		return 1;
	}
	return 0;
}

std::ostream& operator << (std::ostream& stream, const MatrKnapItem& item)
{
	stream << item.name;
	return stream;
}

std::ostream& operator << (std::ostream& stream, MatrKnapItem* item)
{
	stream << item->name;
	return stream;
}

std::ostream& operator << (std::ostream& stream, const MatrKnapContent& knap)
{
	if (knap.GetAmount() > 0)
	{
		for (int ii = 0; ii < knap.GetAmount() - 1; ii++)
		{
			stream << knap.GetItem(ii) << ", ";
		}
		stream << knap.GetItem(knap.GetAmount() - 1);
	}
	stream << knap.GetMatr();
	return stream;
}

std::ostream& operator << (std::ostream& stream, MatrKnapContent* knap)
{
	if (knap->GetAmount() > 0)
	{
		for (int ii = 0; ii < knap->GetAmount() - 1; ii++)
		{
			stream << knap->GetItem(ii) << ", ";
		}
		stream << knap->GetItem(knap->GetAmount() - 1) << "\n";
	}
	stream << knap->GetMatr();
	return stream;
}

#endif