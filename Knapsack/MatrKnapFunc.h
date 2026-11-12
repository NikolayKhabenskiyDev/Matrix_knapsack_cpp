#ifndef MATRKNAPFUNC_H
#define MATRKNAPFUNC_H

#include<string>
#include <iostream>
#include <iomanip>
#include "Matriñes/RectangleMatrix.h"
#include "Matriñes/MatrixFunctions.h"
#include "Knapsack.h"
#include "MatrKnap.h"
#include "SortMatrKnap.h"
#include "Trees/Node.h"
#include "Trees/ArrayNode.h"
#include "Trees/DictionaryTree.h"
#include "Trees/ArrayTree.h"

DictArrTree<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>* AllocateItems
    (DictArrTree<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>* solution_tree,
    ArrNode<Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>*>* current_node,
    ArraySequenceMut<MatrKnapItem*>* items, int amount, int index)
{
    if (index < amount)
    {
        if ((current_node->GetData(0)->GetData()->GetWeight() + items->Get(index)->weight) > current_node->GetData(0)->GetData()->GetMaxWeight())
        {
            AllocateItems(solution_tree, current_node, items, amount, index + 1);
        }
        else
        {
            ArraySequenceMut<Pair<int, int>>** arr_corner_coord =
                new ArraySequenceMut<Pair<int, int>>* [current_node->GetArity()];
            ArraySequenceMut<RectangleMatrix<int>>** matr_variants =
                new ArraySequenceMut<RectangleMatrix<int>>*[current_node->GetArity()];

            for (int ii = 0; ii < current_node->GetArity() - 1; ii++)
            {
                arr_corner_coord[ii] = new ArraySequenceMut<Pair<int, int>>();
                matr_variants[ii] = FindAllFit(current_node->GetData(ii)->GetData()->GetMatr(),
                    items->Get(index)->GetMatr(), arr_corner_coord[ii]);
                matr_variants[ii]->Prepend(current_node->GetData(ii)->GetData()->GetMatr());
                arr_corner_coord[ii]->Prepend(Pair<int, int>(-1, -1));
            }

            ArraySequenceMut<ArraySequenceMut<MatrKnapContent*>*>* knap_variants =
                new ArraySequenceMut<ArraySequenceMut<MatrKnapContent*>*>();
            for (int ii = 0; ii < current_node->GetArity() - 1; ii++)
            {
                ArraySequenceMut<MatrKnapContent*>* temp_array = new ArraySequenceMut<MatrKnapContent*>();
                knap_variants->Append(temp_array);
                knap_variants->Get(ii)->Append(current_node->GetData(ii)->GetData());
                for (int jj = 1; jj < matr_variants[ii]->GetLength(); jj++)
                {
                    Pair<int, int> temp_coord = arr_corner_coord[ii]->Get(jj);
                    MatrKnapContent* temp_knap = new MatrKnapContent(current_node->GetData(ii)->GetData());
                    knap_variants->Get(ii)->Append(temp_knap->AddElem
                        (items->Get(index), temp_coord.GetKey(), temp_coord.GetData()));
                }
            }
            

            ArraySequenceMut<ArraySequenceMut<Pair<int, int>>*>* coord_variants =
                new ArraySequenceMut<ArraySequenceMut<Pair<int, int>>*>();
            for (int ii = 0; ii < current_node->GetArity() - 1; ii++)
            {
                ArraySequenceMut<Pair<int, int>>* temp_array = new ArraySequenceMut<Pair<int, int>>();
                coord_variants->Append(temp_array);
                coord_variants->Get(ii)->Append(Pair<int, int>(-1, -1));
                for (int jj = 1; jj < matr_variants[ii]->GetLength(); jj++)
                {
                    Pair<int, int> temp_coord = arr_corner_coord[ii]->Get(jj);
                    coord_variants->Get(ii)->Append(Pair<int, int>(temp_coord.GetKey(), temp_coord.GetData()));
                }
            }

            ArraySequenceMut<ArraySequenceMut<ArraySequenceMut<Pair<int, int>>*>*>* path_variants =
                new ArraySequenceMut<ArraySequenceMut<ArraySequenceMut<Pair<int, int>>*>*>(current_node->GetArity());
            for (int ii = 0; ii < current_node->GetArity() - 1; ii++)
            {
                ArraySequenceMut<ArraySequenceMut<Pair<int, int>>*>* temp_array =
                    new ArraySequenceMut<ArraySequenceMut<Pair<int, int>>*>();
                path_variants->Append(temp_array);
                for (int jj = 0; jj < matr_variants[ii]->GetLength(); jj++)
                {
                    ArraySequenceMut<Pair<int, int>>* temp_path = 
                        new ArraySequenceMut<Pair<int, int>>(current_node->GetData(ii)->GetKey());
                    temp_path->Append(coord_variants->Get(ii)->Get(jj));
                    path_variants->Get(ii)->Append(temp_path);
                }
            }

            ArraySequenceMut<Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>*>** elem_variants =
                new ArraySequenceMut<Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>*>* [current_node->GetArity()];
            for (int ii = 0; ii < current_node->GetArity() - 1; ii++)
            {
                elem_variants[ii] = new ArraySequenceMut<Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>*>
                    (matr_variants[ii]->GetLength());
                for (int jj = 0; jj < matr_variants[ii]->GetLength(); jj++)
                {
                    Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>* temp_elem =
                        new Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>
                        (path_variants->Get(ii)->Get(jj), knap_variants->Get(ii)->Get(jj));
                    elem_variants[ii]->Append(temp_elem);
                }
            }

            for (int ii = 0; ii < current_node->GetArity() - 1; ii++)
            {
                for (int jj = 0; jj < matr_variants[ii]->GetLength(); jj++)
                {
                    solution_tree->InsertElem(elem_variants[ii]->Get(jj), matr_variants[ii]->GetLength() + 1);
                }
            }
            for (int ii = 0; ii < current_node->GetArity(); ii++)
            {
                if (current_node->GetChilds(ii) != nullptr)
                {
                    AllocateItems(solution_tree, current_node->GetChilds(ii), items, amount, index + 1);
                }
            }
        }
    }
    return solution_tree;
}

DictArrTree<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>* AllocateItems
    (ArraySequenceMut<MatrKnapItem*>* items, MatrKnapContent* empty_knapsack, int amount, int index)
{
    if (index < amount)
    {
        if (items->Get(index)->weight > empty_knapsack->GetMaxWeight())
        {
            AllocateItems(items, empty_knapsack, amount, index + 1);
        }
        else
        {
            ArraySequenceMut<Pair<int, int>>* arr_corner_coord = new ArraySequenceMut<Pair<int, int>>();
            ArraySequenceMut<RectangleMatrix<int>>* matr_variants = new ArraySequenceMut<RectangleMatrix<int>>();
            matr_variants = FindAllFit(empty_knapsack->GetMatr(), items->Get(index)->GetMatr(), arr_corner_coord);
            matr_variants->Prepend(empty_knapsack->GetMatr());
            arr_corner_coord->Prepend(Pair<int, int>(-1, -1));


            ArraySequenceMut<MatrKnapContent*>* knap_variants = new ArraySequenceMut<MatrKnapContent*>();
            knap_variants = new ArraySequenceMut<MatrKnapContent*>();
            knap_variants->Append(empty_knapsack);
            for (int ii = 1; ii < matr_variants->GetLength(); ii++)
            {
                Pair<int, int> temp_coord = arr_corner_coord->Get(ii);
                MatrKnapContent* temp_knapsack = new MatrKnapContent(empty_knapsack);
                knap_variants->Append(temp_knapsack->AddElem(items->Get(index), temp_coord.GetKey(), temp_coord.GetData()));
            }

            ArraySequenceMut<Pair<int, int>>* coord_variants = new ArraySequenceMut<Pair<int, int>>();
            coord_variants = new ArraySequenceMut<Pair<int, int>>();
            coord_variants->Append(Pair<int, int>(-1, -1));
            for (int ii = 1; ii < matr_variants->GetLength(); ii++)
            {
                Pair<int, int> temp_coord = arr_corner_coord->Get(ii);
                coord_variants->Append(Pair<int, int>(temp_coord.GetKey(), temp_coord.GetData()));
            }

            ArraySequenceMut<ArraySequenceMut<Pair<int, int>>*>* path_variants =
                new ArraySequenceMut<ArraySequenceMut<Pair<int, int>>*>();
            path_variants = new ArraySequenceMut<ArraySequenceMut<Pair<int, int>>*>(matr_variants->GetLength());
            ArraySequenceMut<Pair<int, int>>* current_path;
            for (int ii = 0; ii < matr_variants->GetLength(); ii++)
            {
                current_path = new ArraySequenceMut<Pair<int, int>>();
                current_path->Append(coord_variants->Get(ii));
                path_variants->Append(current_path);
            }

            ArraySequenceMut<Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>*>* elem_variants =
                new ArraySequenceMut<Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>*>();
            elem_variants = new ArraySequenceMut<Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>*>(matr_variants->GetLength());
            for (int jj = 0; jj < matr_variants->GetLength(); jj++)
            {
                Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>* temp_elem =
                    new Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>
                    (path_variants->Get(jj), knap_variants->Get(jj));
                elem_variants->Append(temp_elem);
            }

            DictArrTree<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>* solution_tree =
                new DictArrTree<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>(matr_variants->GetLength() + 1);
            for (int jj = 0; jj < matr_variants->GetLength(); jj++)
            {
                solution_tree->InsertElem(elem_variants->Get(jj), matr_variants->GetLength() + 1);
            }

            return AllocateItems(solution_tree, solution_tree->GetRoot(), items, amount, index + 1);
        }
    }
    else
    {
        return nullptr;
    }
}

ArraySequenceMut<MatrKnapContent*>* FindBestContent (ArraySequenceMut<Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>*>* leaves_seq)
{
    ArraySequenceMut<MatrKnapContent*>* best_array = new ArraySequenceMut<MatrKnapContent*>();
    if (leaves_seq->GetLength() == 0)
    {
        return best_array;
    }
    else
    {
        MatrKnapContent* best_content = leaves_seq->GetFirst()->GetData();
        for (int ii = 1; ii < leaves_seq->GetLength(); ii++)
        {
            if ((leaves_seq->Get(ii)->GetData()->GetValue() > best_content->GetValue()) &&
                leaves_seq->Get(ii)->GetData()->GetWeight() <= leaves_seq->Get(ii)->GetData()->GetMaxWeight())
            {
                best_content = leaves_seq->Get(ii)->GetData();
            }
        }
        for (int ii = 1; ii < leaves_seq->GetLength(); ii++)
        {
            if (leaves_seq->Get(ii)->GetData()->GetValue() == best_content->GetValue())
            {
                best_array->Append(leaves_seq->Get(ii)->GetData());
            }
        }
        return best_array;
    }
}

ArraySequenceMut<MatrKnapContent*>* MatrKnapProblemUser(ArraySequenceMut<MatrKnapItem*>* items, int amount, int limit_weight, int knap_height, int knap_width)
{
    std::cout << items;
    items = SortMatrKnap(items, amount);
    std::cout << items;
    MatrKnapContent* empty_knapsack = new MatrKnapContent(limit_weight, knap_height, knap_width);

    DictArrTree<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>* solution_tree =
        AllocateItems(items, empty_knapsack, amount, 0);
    
    std::cout << "Print Tree?" << "\n" << "1. Yes" << "\n" << "2. No" << "\n";
    int print = get_int();
    while ((print < 1) || (print > 2))
    {
        std::cout << "Choose correct number" << "\n";
        print = get_int();
    }
    if (print == 1)
    {
        std::cout << solution_tree;
    }

    ArraySequenceMut<Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>*>* leaves = GetLeaves(solution_tree);
    ArraySequenceMut<MatrKnapContent*>* best = FindBestContent(leaves);
    std::cout << ToString(best);
    delete solution_tree;
    delete leaves;
    return best;
}

ArraySequenceMut<MatrKnapContent*>* MatrKnapProblem(ArraySequenceMut<MatrKnapItem*>* items, int amount, int limit_weight, int knap_height, int knap_width)
{
    items = SortMatrKnap(items, amount);
    MatrKnapContent* empty_knapsack = new MatrKnapContent(limit_weight, knap_height, knap_width);

    DictArrTree<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>* solution_tree =
        AllocateItems(items, empty_knapsack, amount, 0);

    ArraySequenceMut<Pair<ArraySequenceMut<Pair<int, int>>*, MatrKnapContent*>*>* leaves = GetLeaves(solution_tree);
    ArraySequenceMut<MatrKnapContent*>* best = FindBestContent(leaves);
    delete solution_tree;
    delete leaves;
    return best;
}

#endif
