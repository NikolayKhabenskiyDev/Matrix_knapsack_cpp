#ifndef MATRIXFUNCTIONS_H
#define MATRIXFUNCTIONS_H

#include "RectangleMatrix.h"
#include "Trees/DictionaryTree.h"

template<class T>
RectangleMatrix<T>* AddSubMatrix(RectangleMatrix<T>* big_matr, RectangleMatrix<T>* sub_matr, int corner_row_index, int corner_col_index)
{
	if (corner_row_index + sub_matr->GetHeight() > big_matr->GetHeight())
	{
		throw std::out_of_range("Error: Height index out of range\n");
	}
	if (corner_col_index + sub_matr->GetWidth() > big_matr->GetWidth())
	{
		throw std::out_of_range("Error: Width index out of range\n");
	}
	RectangleMatrix<int>* result_matr = new RectangleMatrix<int>(big_matr);
	for (int ii = 0; ii < sub_matr->GetHeight(); ii++)
	{
		for (int jj = 0; jj < sub_matr->GetWidth(); jj++)
		{
			T temp_elem = big_matr->GetElem(corner_row_index + ii, corner_col_index + jj) + sub_matr->GetElem(ii, jj);
			result_matr->SetElem(corner_row_index + ii, corner_col_index + jj, temp_elem);
		}
	}
	return result_matr;
}

template<class T>
bool IsFit(RectangleMatrix<T>* matr1, RectangleMatrix<T>* matr2)
{
	if (matr1->GetHeight() != matr2->GetHeight() || matr1->GetWidth() != matr2->GetWidth())
	{
		throw std::out_of_range("Error: Matrixes have different size");
	}
	for (int ii = 0; ii < matr1->GetHeight(); ii++)
	{
		for (int jj = 0; jj < matr1->GetWidth(); jj++)
		{
			if (matr1->GetElem(ii, jj) != T() && matr2->GetElem(ii, jj) != T())
			{
				return 0;
			}
		}
	}
	return 1;
}

template<class T>
bool IsFit(RectangleMatrix<T>* big_matr, RectangleMatrix<T>* small_matr, int corner_row_index, int corner_col_index)
{
	if (corner_row_index + small_matr->GetHeight() > big_matr->GetHeight())
	{
		return 0;
	}
	if (corner_col_index + small_matr->GetWidth() > big_matr->GetWidth())
	{
		return 0;
	}
	RectangleMatrix<T>* sub_matr = big_matr->GetSubMatrix(corner_row_index, corner_row_index + small_matr->GetHeight() - 1,
															corner_col_index, corner_col_index + small_matr->GetWidth() - 1);
	return IsFit<T>(sub_matr, small_matr);
}

template<class T>
int CountAllFit(RectangleMatrix<T>* big_matr, RectangleMatrix<T>* small_matr)
{
	int fit_amount = 0;
	ArraySequenceMut<RectangleMatrix<T>>* matr_array = new ArraySequenceMut<RectangleMatrix<T>>();
	for (int ii = 0; ii < big_matr->GetHeight(); ii++)
	{
		for (int jj = 0; jj < big_matr->GetWidth(); jj++)
		{
			if (IsFit<T>(big_matr, small_matr, ii, jj))
			{
				fit_amount++;
			}
		}
	}
	return fit_amount;
}

template<class T>
ArraySequenceMut<RectangleMatrix<T>>* FindAllFit(RectangleMatrix<T>* big_matr, RectangleMatrix<T>* small_matr)
{
	ArraySequenceMut<RectangleMatrix<T>>* matr_array = new ArraySequenceMut<RectangleMatrix<T>>();
	for (int ii = 0; ii < big_matr->GetHeight(); ii++)
	{
		for (int jj = 0; jj < big_matr->GetWidth(); jj++)
		{
			if (IsFit<T>(big_matr, small_matr, ii, jj))
			{
				matr_array->Append(AddSubMatrix<T>(big_matr, small_matr, ii, jj));
			}
		}
	}
	return matr_array;
}

template<class T>
ArraySequenceMut<RectangleMatrix<T>>* FindAllFit(RectangleMatrix<T>* big_matr, RectangleMatrix<T>* small_matr, ArraySequenceMut<Pair<int, int>>* corner_coord_array)
{
	ArraySequenceMut<RectangleMatrix<T>>* matr_array = new ArraySequenceMut<RectangleMatrix<T>>();
	for (int ii = 0; ii < big_matr->GetHeight(); ii++)
	{
		for (int jj = 0; jj < big_matr->GetWidth(); jj++)
		{
			if (IsFit<T>(big_matr, small_matr, ii, jj))
			{
				matr_array->Append(AddSubMatrix<T>(big_matr, small_matr, ii, jj));
				corner_coord_array->Append(Pair<int, int>(ii, jj));
			}
		}
	}
	return matr_array;
}

#endif