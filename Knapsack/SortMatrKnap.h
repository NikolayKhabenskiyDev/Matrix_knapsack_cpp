#ifndef SORTMATRKNAP_H
#define SORTMATRKNAP_H

#include "Matriñes/RectangleMatrix.h"
#include "Matriñes/MatrixFunctions.h"
#include "Knapsack.h"
#include "MatrKnap.h"

int FindMatrFullness(RectangleMatrix<int>* matr)
{
	int full_cell_amount = 0;
	for (int ii = 0; ii < matr->GetHeight(); ii++)
	{
		for (int ii2 = 0; ii2 < matr->GetWidth(); ii2++)
		{
			if (matr->GetElem(ii, ii2) != 0)
			{
				full_cell_amount++;
			}
		}
	}
	return full_cell_amount;
}

ArraySequenceMut<MatrKnapItem*>* SortMatrKnap(ArraySequenceMut<MatrKnapItem*>* items, int length)
{
	if (length < 2)
	{
		return items;
	}
	else
	{
		ArraySequenceMut<MatrKnapItem*>* sorted_items = new ArraySequenceMut<MatrKnapItem*>();
		for (int ii = length - 1; ii > 0; ii--)
		{
			for (int ii2 = 0; ii2 < ii; ii2++)
			{
				if (FindMatrFullness(items->Get(ii2)->GetMatr()) < FindMatrFullness(items->Get(ii2 + 1)->GetMatr()))
				{
					MatrKnapItem* temp_elem = new MatrKnapItem(*items->Get(ii2));
					delete items->Get(ii2);
					items->Set(items->Get(ii2 + 1), ii2);
					items->Set(temp_elem, ii2 + 1);
				}
			}
		}
		return items;
	}

}

#endif