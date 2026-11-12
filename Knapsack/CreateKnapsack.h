#ifndef CREATEKNAPSACK_H
#define CREATEKNAPSACK_H

#include "Interfaces/SafeInput.h"
#include "Knapsack.h"
#include "MatrKnap.h"
#include "Generation/RandomGenerator.h"
#include "Matriñes/CreateMatrix.h"

KnapsackItem CreateItem()
{
    std::cout << "Print name of item" << "\n";
    std::string name;
    std::cin >> name;

    std::cout << "Print weight of item" << "\n";
    int weight = get_int();
    while (weight < 0)
    {
        std::cout << "Choose correct number" << "\n";
        weight = get_int();
    }

    std::cout << "Print value of item" << "\n";
    int value = get_int();
    while (value < 0)
    {
        std::cout << "Choose correct number" << "\n";
        value = get_int();
    }

    KnapsackItem item = KnapsackItem(name, weight, value);
    return item;
}

KnapsackContent* CreateKnap()
{
    std::cout << "Print max weight" << "\n";
    int max_weight = get_int();
    while (max_weight < 0)
    {
        std::cout << "Choose correct number" << "\n";
        max_weight = get_int();
    }
    KnapsackContent* knap = new KnapsackContent(max_weight);
    return knap;
}

KnapsackItem* CreateItemArray(int arr_length)
{
    KnapsackItem* items = new KnapsackItem[arr_length];

    std::cout << "Choose type of items creation" << "\n" << "1. scan" << "\n"
        << "2. random (with limited parameters)" << "\n" << "3. completely random" << "\n";
    int generate_type = get_int();
    while ((generate_type < 1) || (generate_type > 3))
    {
        std::cout << "Choose correct number\n" << "\n";
        generate_type = get_int();
    }
    if (generate_type == 1)
    {
        for (int ii = 0; ii < arr_length; ii++)
        {
            std::cout << "Item " << ii + 1 << "\n";
            items[ii] = CreateItem();
            std::cout << ToString(items[ii]);
        }
    }
    if (generate_type == 2)
    {
        std::cout << "Print max weight of one item" << "\n";
        int max_weight = get_int();
        while (max_weight < 0)
        {
            std::cout << "Choose correct number" << "\n";
            max_weight = get_int();
        }
        std::cout << "Print max value of one item" << "\n";
        int max_value = get_int();
        while (max_value < 0)
        {
            std::cout << "Choose correct number" << "\n";
            max_value = get_int();
        }

        for (int ii = 0; ii < arr_length; ii++)
        {
            std::cout << "Item " << ii + 1 << "\n";
            items[ii] = KnapItemGen(max_weight, max_value);
            std::cout << ToString(items[ii]);
        }
    }
    if (generate_type == 3)
    {
        for (int ii = 0; ii < arr_length; ii++)
        {
            std::cout << "Item " << ii + 1 << "\n";
            items[ii] = KnapItemGen(10, 10);
            std::cout << ToString(items[ii]);
        }
    }
    return items;
}

MatrKnapItem* CreateMatrItem(int item_index)
{
    std::cout << "Print name of item" << "\n";
    std::string name;
    std::cin >> name;

    std::cout << "Print weight of item" << "\n";
    int weight = get_int();
    while (weight < 0)
    {
        std::cout << "Choose correct number" << "\n";
        weight = get_int();
    }

    std::cout << "Print value of item" << "\n";
    int value = get_int();
    while (value < 0)
    {
        std::cout << "Choose correct number" << "\n";
        value = get_int();
    }

    std::cout << "Print height of item" << "\n";
    int height = get_int();
    while (height < 1)
    {
        std::cout << "Choose correct number" << "\n";
        height = get_int();
    }

    std::cout << "Print width of item" << "\n";
    int width = get_int();
    while (width < 0)
    {
        std::cout << "Choose correct number" << "\n";
        width = get_int();
    }

    std::cout << "Choose type of matrix creation" << "\n" << "1. scan" << "\n"
        << "2. choose filling pattern" << "\n" << "3. random" << "\n";
    int gen_type = get_int();
    while (gen_type < 1 || gen_type > 3)
    {
        std::cout << "Choose correct number" << "\n";
        gen_type = get_int();
    }

    RectangleMatrix<int>* matr = nullptr;
    if (gen_type == 1)
    {
        matr = new RectangleMatrix<int>(height, width);
        std::cout << "Print content of cells" << "\n";
        for (int ii = 0; ii < height; ii++)
        {
            for (int ii2 = 0; ii2 < width; ii2++)
            {
                std::cout << ii * width + ii2 + 1 << " cell:" << "\n";
                int cell = get_int();
                matr->SetElem(ii, ii2, cell);
                std::cout << "Matr:\n" << matr << "\n";
            }
        }
    }
    if (gen_type == 2)
    {
        matr = CreateMatrixChoosePattern(height, width, item_index);
    }
    if (gen_type == 3)
    {
        matr = MatrixGen(height, width, item_index);
    }

    MatrKnapItem* item = new MatrKnapItem(name, weight, value, matr);
    return item;
}

MatrKnapContent* CreateMatrKnap()
{
    std::cout << "Print max weight of knapsack" << "\n";
    int max_weight = get_int();
    while (max_weight < 0)
    {
        std::cout << "Choose correct number" << "\n";
        max_weight = get_int();
    }

    std::cout << "Print height of knapsack" << "\n";
    int height = get_int();
    while (height < 1)
    {
        std::cout << "Choose correct number" << "\n";
        height = get_int();
    }

    std::cout << "Print width of knapsack" << "\n";
    int width = get_int();
    while (width < 0)
    {
        std::cout << "Choose correct number" << "\n";
        width = get_int();
    }

    MatrKnapContent* knap = new MatrKnapContent(max_weight, height, width);
    return knap;
}

MatrKnapItem** CreateMatrItemArray(int arr_length)
{
    MatrKnapItem** items = new MatrKnapItem*[arr_length];

    std::cout << "Choose type of items creation" << "\n" << "1. scan" << "\n"
        << "2. random (with limited parameters)" << "\n" << "3. completely random" << "\n";
    int generate_type = get_int();
    while ((generate_type < 1) || (generate_type > 3))
    {
        std::cout << "Choose correct number\n" << "\n";
        generate_type = get_int();
    }
    if (generate_type == 1)
    {
        for (int ii = 0; ii < arr_length; ii++)
        {
            std::cout << "Item " << ii + 1 << "\n";
            items[ii] = CreateMatrItem(ii + 1);
            std::cout << ToString(items[ii]);
        }
    }
    if (generate_type == 2)
    {
        std::cout << "Print max weight of one item" << "\n";
        int max_weight = get_int();
        while (max_weight < 0)
        {
            std::cout << "Choose correct number" << "\n";
            max_weight = get_int();
        }

        std::cout << "Print max value of one item" << "\n";
        int max_value = get_int();
        while (max_value < 0)
        {
            std::cout << "Choose correct number" << "\n";
            max_value = get_int();
        }

        std::cout << "Print max height of one item" << "\n";
        int max_height = get_int();
        while (max_height < 1)
        {
            std::cout << "Choose correct number" << "\n";
            max_height = get_int();
        }

        std::cout << "Print max width of one item" << "\n";
        int max_width = get_int();
        while (max_width < 1)
        {
            std::cout << "Choose correct number" << "\n";
            max_width = get_int();
        }

        for (int ii = 0; ii < arr_length; ii++)
        {
            std::cout << "Item " << ii + 1 << "\n";
            items[ii] = MatrKnapItemGen(max_weight, max_value, max_height, max_width, ii + 1);
            std::cout << ToString(items[ii]);
        }
    }
    if (generate_type == 3)
    {
        for (int ii = 0; ii < arr_length; ii++)
        {
            std::cout << "Item " << ii + 1 << "\n";
            items[ii] = MatrKnapItemGen(10, 10, 4, 4, ii + 1);
            std::cout << ToString(items[ii]);
        }
    }
    return items;
}

#endif