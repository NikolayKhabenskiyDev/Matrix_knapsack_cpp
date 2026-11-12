#ifndef TOSTRING_H
#define TOSTRING_H

#include "Knapsack/Knapsack.h"
#include "Knapsack/MatrKnap.h"
#include "Trees/Node.h"
#include "Trees/ArrayNode.h"


std::string PrintItems (MatrKnapContent knap)
{
    std::string stream = "";
    if (knap.GetAmount() > 0)
    {
        for (int ii = 0; ii < knap.GetAmount() - 1; ii++)
        {
            stream = stream + knap.GetItem(ii)->name + ", ";
        }
        stream = stream + knap.GetItem(knap.GetAmount() - 1)->name;
    }
    return stream;
}

std::string ToString(const KnapsackItem& item)
{
    std::string stream = item.name + ": " + std::to_string(item.weight)
        + " kg, " + std::to_string(item.value) + " $\n";
    return stream;
}

std::string ToString(KnapsackItem* item)
{
    std::string stream = item->name + ": " + std::to_string(item->weight)
        + " kg, " + std::to_string(item->value) + " $\n";
    return stream;
}

std::string ToString(const KnapsackContent& knap)
{
    std::string stream = "";
    if (knap.GetAmount() > 0)
    {
        for (int ii = 0; ii < knap.GetAmount() - 1; ii++)
        {
            stream = stream + knap.GetItem(ii).name + ", ";
        }
        stream = stream + knap.GetItem(knap.GetAmount() - 1).name + "; ";
        stream = stream + std::to_string(knap.GetWeight()) + " kg, ";
        stream = stream + std::to_string(knap.GetValue()) + " $\n";
    }
    return stream;
    return stream;
}

std::string ToString(KnapsackContent* knap)
{
    std::string stream = "";
    if (knap->GetAmount() > 0)
    {
        for (int ii = 0; ii < knap->GetAmount() - 1; ii++)
        {
            stream = stream + knap->GetItem(ii).name + ", ";
        }
        stream = stream + knap->GetItem(knap->GetAmount() - 1).name + "; ";
        stream = stream + std::to_string(knap->GetWeight()) + " kg, ";
        stream = stream + std::to_string(knap->GetValue()) + " $\n";
    }
    return stream;
}

std::string ToString(ArraySequenceMut<KnapsackContent>* seq)
{
    if (seq->GetLength() > 0)
    {
        std::string stream = "";
        for (int ii = 0; ii < seq->GetLength(); ii++)
        {
            stream = stream + ToString(seq->Get(ii)) + "\n\n";
        }
        return stream;
    }
    else
    {
        return "No knapsacks\n\n";
    }
}

std::string ToString(ArraySequenceMut<KnapsackContent*>* seq)
{
    if (seq->GetLength() > 0)
    {
        std::string stream = "";
        for (int ii = 0; ii < seq->GetLength(); ii++)
        {
            stream = stream + ToString(seq->Get(ii)) + "\n\n";
        }
        return stream;
    }
    else
    {
        return "No knapsacks\n\n";
    }
}

std::string ToString(const MatrKnapItem& item)
{
    std::string stream = item.name + ": " + std::to_string(item.weight)
        + " kg, " + std::to_string(item.value) + " $\n" + ToString<int>(item.matr);
    return stream;
}

std::string ToString(MatrKnapItem* item)
{
    std::string stream = item->name + ": " + std::to_string(item->weight)
        + " kg, " + std::to_string(item->value) + " $\n" + ToString<int>(item->matr);
    return stream;
}

std::string ToString(const MatrKnapContent& knap)
{
    std::string stream = "";
    if (knap.GetAmount() > 0)
    {
        for (int ii = 0; ii < knap.GetAmount() - 1; ii++)
        {
            stream = stream + knap.GetItem(ii)->name + ", ";
        }
        stream = stream + knap.GetItem(knap.GetAmount() - 1)->name + "; ";
        stream = stream + std::to_string(knap.GetWeight()) + " kg, ";
        stream = stream + std::to_string(knap.GetValue()) + " $\n";
    }
    stream = stream + ToString<int>(knap.GetMatr());
    return stream;
}

std::string ToString(MatrKnapContent* knap)
{
    std::cout << knap;
    std::string stream = "";
    if (knap->GetAmount() > 0)
    {
        for (int ii = 0; ii < knap->GetAmount() - 1; ii++)
        {
            stream = stream + knap->GetItem(ii)->name + ", ";
        }
        stream = stream + knap->GetItem(knap->GetAmount() - 1)->name + "; ";
        stream = stream + std::to_string(knap->GetWeight()) + " kg, ";
        stream = stream + std::to_string(knap->GetValue()) + " $\n";
    }
    stream = stream + ToString<int>(knap->GetMatr());
    return stream;
}

std::string ToString(ArraySequenceMut<MatrKnapItem*>* seq)
{
    if (seq->GetLength() > 0)
    {
        std::string stream = "";
        for (int ii = 0; ii < seq->GetLength(); ii++)
        {
            stream = stream + ToString(seq->Get(ii)) + "\n\n";
        }
        return stream;
    }
}

std::string ToString(ArraySequenceMut<MatrKnapContent*>* seq)
{
    if (seq->GetLength() > 0)
    {
        std::string stream = "";
        for (int ii = 0; ii < seq->GetLength(); ii++)
        {
            stream = stream + ToString(seq->Get(ii)) + "\n\n";
        }
        return stream;
    }
    else
    {
        return "No knapsacks\n\n";
    }
}

#endif