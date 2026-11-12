#ifndef INTERFACE_H
#define INTERFACE_H

#include "Interfaces/SafeInput.h"
#include "Knapsack/Knapsack.h"
#include "Knapsack/MatrKnap.h"
#include "Generation/RandomGenerator.h"
#include "Knapsack/CreateKnapsack.h"
#include "Knapsack/KnapsackFunctions.h"
#include "Knapsack/MatrKnapFunc.h"
#include "ToString.h"

void Interface()
{
	bool restart = 1;
	while (restart)
	{
		std::cout << "Choose type of knapsack problem" << "\n" << "1. Basic" << "\n" << "2. Matrix" << "\n";
		int knap_type = get_int();
		while ((knap_type < 1) || (knap_type > 2))
		{
			std::cout << "Choose correct number\n" << "\n";
			knap_type = get_int();
		}
		std::cout << "Print amount of items you want to create" << "\n";
		int arr_length = get_int();
		while (arr_length < 1)
		{
			std::cout << "Choose correct number" << "\n";
			arr_length = get_int();
		}

		std::cout << "Print max weight of knapsack" << "\n";
		int knap_weight = get_int();
		while (knap_weight < 1)
		{
			std::cout << "Choose correct number" << "\n";
			knap_weight = get_int();
		}

		if (knap_type == 1)
		{
			KnapsackItem* items = CreateItemArray(arr_length);
			KnapsackProblemUser(items, knap_weight, arr_length);
		}
		if (knap_type == 2)
		{
			std::cout << "Print height of knapsack" << "\n";
			int knap_height = get_int();
			while (knap_height < 1)
			{
				std::cout << "Choose correct number" << "\n";
				knap_height = get_int();
			}
			std::cout << "Print width of knapsack" << "\n";
			int knap_width = get_int();
			while (knap_width < 1)
			{
				std::cout << "Choose correct number" << "\n";
				knap_width = get_int();
			}
			ArraySequenceMut<MatrKnapItem*>* items = new ArraySequenceMut<MatrKnapItem*>(CreateMatrItemArray(arr_length), arr_length);
			MatrKnapProblemUser(items, arr_length, knap_weight, knap_height, knap_width);
		}

		std::cout << "Continue?" << "\n" << "1. Yes" << "\n" << "2. No" << "\n";
		int end_or_not = get_int();
		while ((end_or_not < 1) || (end_or_not > 3))
		{
			std::cout << "Choose correct number\n" << "\n";
			end_or_not = get_int();
		}
		if (end_or_not == 2)
		{
			restart = 0;
		}
	}
}

#endif