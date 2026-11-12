#ifndef KNAPSACKFUNCTIONS_H
#define KNAPSACKFUNCTIONS_H

#include "BasicStructures/DynamicArray.h"
#include "BasicStructures/Sequence.h"
#include "BasicStructures/ArraySequence.h"
#include "Trees/Node.h"
#include "Knapsack.h"
#include "Trees/BinSearchTree.h"
#include "Trees/DictionaryTree.h"
#include "Interfaces/ToString.h"

DictBinTree<std::string, KnapsackContent>* AllocateItems
    (DictBinTree<std::string, KnapsackContent>* dict, Pair<std::string, KnapsackContent> current_knap,
    KnapsackItem* items, int amount, int index)
{
    if (index < amount)
    {
        Pair<std::string, KnapsackContent> knap_add;
        Pair<std::string, KnapsackContent> knap_not_add;
        knap_add.SetData(current_knap.GetData().AddElem(items[index]));
        knap_add.SetKey(current_knap.GetKey() + "1");
        knap_not_add.SetData(current_knap.GetData());
        knap_not_add.SetKey(current_knap.GetKey() + "0");
        dict->InsertNode(knap_not_add);
        if (knap_add.GetData().GetWeight() <= knap_add.GetData().GetMaxWeight())
        {
            dict->InsertNode(knap_add);
        }
        AllocateItems(dict, knap_not_add, items, amount, index + 1);
        if (knap_add.GetData().GetWeight() <= knap_add.GetData().GetMaxWeight())
        {
            AllocateItems(dict, knap_add, items, amount, index + 1);
        }
    }
    return dict;
}

ArraySequenceMut<KnapsackContent>* FindBestContent(ArraySequenceMut<Pair<std::string, KnapsackContent>>* leaves_seq)
{
    ArraySequenceMut<KnapsackContent>* best_array = new ArraySequenceMut<KnapsackContent>();
    if (leaves_seq->GetLength() == 0)
    {
        return best_array;
    }
    else
    {
        KnapsackContent best_content = leaves_seq->GetFirst().GetData();
        for (int ii = 1; ii < leaves_seq->GetLength(); ii++)
        {
            if ((leaves_seq->Get(ii).GetData().GetValue() > best_content.GetValue()) &&
                leaves_seq->Get(ii).GetData().GetWeight() <= leaves_seq->Get(ii).GetData().GetMaxWeight())
            {
                best_content = leaves_seq->Get(ii).GetData();
            }
        }
        if (best_content.GetAmount() != 0)
        {
            for (int ii = 0; ii < leaves_seq->GetLength(); ii++)
            {
                if (leaves_seq->Get(ii).GetData().GetValue() == best_content.GetValue())
                {
                    best_array->Append(leaves_seq->Get(ii).GetData());
                }
            }
        }
        return best_array;
    }
}

ArraySequenceMut<KnapsackContent>* KnapsackProblem(KnapsackItem* items, int limit_weight, int amount)
{
    Pair<std::string, KnapsackContent> root = Pair<std::string, KnapsackContent>("", KnapsackContent(limit_weight));

    DictBinTree<std::string, KnapsackContent>* solution_tree = new DictBinTree<std::string, KnapsackContent>(Less);
    solution_tree->InsertNode(root);
    AllocateItems(solution_tree, root, items, amount, 0);
    ArraySequenceMut<Pair<std::string, KnapsackContent>>* leaves = GetLeaves(solution_tree);
    ArraySequenceMut<KnapsackContent>* best_contents = FindBestContent(leaves);
    delete solution_tree;
    delete leaves;
    return best_contents;
}

ArraySequenceMut<KnapsackContent>* KnapsackProblemUser(KnapsackItem* items, int limit_weight, int amount)
{
    Pair<std::string, KnapsackContent> root = Pair<std::string, KnapsackContent>("", KnapsackContent(limit_weight));

    DictBinTree<std::string, KnapsackContent>* solution_tree = new DictBinTree<std::string, KnapsackContent>(Less);
    solution_tree->InsertNode(root);
    AllocateItems(solution_tree, root, items, amount, 0);
    std::cout << "Print Tree?" << "\n" << "1. Yes" << "\n" << "2. No" << "\n";
    int print = get_int();
    while ((print < 0) && (print > 1))
    {
        std::cout << "Choose correct number" << "\n";
        print = get_int();
    }
    if (print == 1)
    {
        std::cout << solution_tree;
    }
    ArraySequenceMut<Pair<std::string, KnapsackContent>>* leaves = GetLeaves(solution_tree);
    ArraySequenceMut<KnapsackContent>* best_contents = FindBestContent(leaves);
    std::cout << ToString(best_contents);
    delete solution_tree;
    delete leaves;
    return best_contents;
}

ArraySequenceMut<KnapsackContent>* KnapsackProblemUser(ArraySequenceMut<KnapsackItem>* items, int limit_weight)
{
    KnapsackItem* items_array = new KnapsackItem[items->GetLength()];
    for (int ii = 0; ii < items->GetLength(); ii++)
    {
        items_array[ii] = items->Get(ii);
    }
    ArraySequenceMut<KnapsackContent>* best_contents = KnapsackProblemUser(items_array, limit_weight, items->GetLength());
    delete[] items_array;
    return  best_contents;
}

#endif