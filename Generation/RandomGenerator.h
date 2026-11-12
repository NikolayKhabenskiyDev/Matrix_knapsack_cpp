#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>
#include<string>
#include <iostream>
#include "Knapsack/Knapsack.h"
#include "knapsack/MatrKnap.h"
#include "NamesArray.h"

KnapsackItem KnapItemGen(int max_weight, int max_value)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> weight_dist(1, max_weight);
	std::uniform_int_distribution<std::mt19937::result_type> value_dist(0, max_value);
	std::uniform_int_distribution<std::mt19937::result_type> name_dist(0, 199);

	int weight = weight_dist(rng);
	int value = value_dist(rng);
	int name_index = name_dist(rng);
	std::string name = item_names[name_index];
	KnapsackItem item = KnapsackItem(name, weight, value);
	return item;
}

MatrKnapItem* MatrKnapItemGen(int max_weight, int max_value, int max_height, int max_width, int elem_number)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> weight_dist(1, max_weight);
	std::uniform_int_distribution<std::mt19937::result_type> value_dist(0, max_value);
	std::uniform_int_distribution<std::mt19937::result_type> height_dist(1, max_height);
	std::uniform_int_distribution<std::mt19937::result_type> width_dist(1, max_width);
	std::uniform_int_distribution<std::mt19937::result_type> density_dist(50, 100);
	std::uniform_int_distribution<std::mt19937::result_type> chance_dist(50, 100);
	std::uniform_int_distribution<std::mt19937::result_type> name_dist(0, 199);

	int weight = weight_dist(rng);
	int value = value_dist(rng);
	int name_index = name_dist(rng);
	std::string name = item_names[name_index];

	int height = height_dist(rng);
	int width = width_dist(rng);
	RectangleMatrix<int>* matr = new RectangleMatrix<int>(height, width);
	int density_percent = density_dist(rng);
	for (int ii = 0; ii < height; ii++)
	{
		for (int jj = 0; jj < width; jj++)
		{
			int chance_fill_cell = chance_dist(rng);
			if (chance_fill_cell < density_percent)
			{
				matr->SetElem(ii, jj, 0);
			}
			else
			{
				matr->SetElem(ii, jj, elem_number);
			}
		}
	}
	matr->SetElem(0, 0, elem_number);
	MatrKnapItem* item = new MatrKnapItem(name, weight, value, matr);
	return item;
}

RectangleMatrix<int>* MatrixGen(int height, int width, int elem_number)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> density_dist(0, 100);
	std::uniform_int_distribution<std::mt19937::result_type> chance_dist(30, 100);

	RectangleMatrix<int>* matr = new RectangleMatrix<int>(height, width);
	int density_percent = density_dist(rng);
	for (int ii = 0; ii < height; ii++)
	{
		for (int jj = 0; jj < width; jj++)
		{
			int chance_fill_cell = chance_dist(rng);
			if (chance_fill_cell < density_percent)
			{
				matr->SetElem(ii, jj, 0);
			}
			else
			{
				matr->SetElem(ii, jj, elem_number);
			}
		}
	}
	return matr;
}

#endif