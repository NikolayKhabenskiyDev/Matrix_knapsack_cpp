#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <iostream>
#include "Headers from Lab2/DynamicArray.h"
#include "Headers from Lab2/Sequence.h"
#include "Headers from Lab2/ArraySequence.h"
#include "Headers from Lab2/FunctionsForMapReduce.h"
#include "RectangleMatrix.h"

template <class T>
RectangleMatrix<T>* AddMatrix(RectangleMatrix<T>* matrix1, RectangleMatrix<T>* matrix2)
{
    if (matrix1->GetWidth() != matrix2->GetWidth())
    {
        throw std::out_of_range("Error: Matrices have different width");
    }
    if (matrix1->GetHeight() != matrix2->GetHeight())
    {
        throw std::out_of_range("Error: Matrices have different height");
    }
    else
    {
        RectangleMatrix<T>* result = new RectangleMatrix<T>(matrix1->GetHeight(), matrix1->GetWidth());
        T temp_elem;
        for (int ii = 0; ii < matrix1->GetHeight(); ii++)
        {
            for (int ii2 = 0; ii2 < matrix1->GetWidth(); ii2++)
            {
                temp_elem = matrix1->GetElem(ii, ii2) + matrix2->GetElem(ii, ii2);
                result->SetElem(ii, ii2, temp_elem);
            }
        }
        return(result);
    }
}

template <class T>
RectangleMatrix<T>* MultiplyByScalar(RectangleMatrix<T>* matrix, const T& scalar)
{
    RectangleMatrix<T>* result = new RectangleMatrix<T>(matrix);
    ArraySequenceMut<T>* temp_row;
    for (int ii = 0; ii < matrix->GetHeight(); ii++)
    {
        temp_row = result->GetRow(ii);
        temp_row->Map(Multiply, scalar);
        result->SetRow(ii, temp_row);
    }
    return(result);
}

template <class T>
RectangleMatrix<T>* MultiplyRow(RectangleMatrix<T>* matrix, T scalar, int row_index)
{
    RectangleMatrix<T>* result = new RectangleMatrix<T>(matrix);
    ArraySequenceMut<T>* temp_row = result->GetRow(row_index);
    temp_row->Map(Multiply, scalar);
    result->SetRow(row_index, temp_row);
    return(result);
}

template <class T>
RectangleMatrix<T>* MultiplyColumn(RectangleMatrix<T>* matrix, const T& scalar, int col_index)
{
    RectangleMatrix<T>* result = new RectangleMatrix<T>(matrix);
    T temp_elem;
    for (int ii = 0; ii < matrix->GetHeight(); ii++)
    {
        temp_elem = (matrix->GetElem(ii, col_index)) * scalar;
        result->SetElem(ii, col_index, temp_elem);
    }
    return(result);
}

template <class T>
RectangleMatrix<T>* AddRow(RectangleMatrix<T>* matrix, int row_index1, int row_index2)
{
    RectangleMatrix<T>* result = new RectangleMatrix<T>(matrix);
    T temp_elem;
    for (int ii = 0; ii < matrix->GetWidth(); ii++)
    {
        temp_elem = (matrix->GetElem(row_index1, ii)) + (matrix->GetElem(row_index2, ii));
        result->SetElem(row_index1, ii, temp_elem);
    }
    return(result);
}

template <class T>
RectangleMatrix<T>* AddColumn(RectangleMatrix<T>* matrix, int col_index1, int col_index2)
{
    RectangleMatrix<T>* result = new RectangleMatrix<T>(matrix);
    T temp_elem;
    for (int ii = 0; ii < matrix->GetHeight(); ii++)
    {
        temp_elem = (matrix->GetElem(ii, col_index1)) + (matrix->GetElem(ii, col_index2));
        result->SetElem(ii, col_index1, temp_elem);
    }
    return(result);
}

template <class T>
RectangleMatrix<T>* SwapRow(RectangleMatrix<T>* matrix, int row_index1, int row_index2)
{
    RectangleMatrix<T>* result = new RectangleMatrix<T>(matrix);
    ArraySequenceMut<T>* temp_row = matrix->GetRow(row_index1);
    result->SetRow(row_index2, temp_row);
    temp_row = matrix->GetRow(row_index2);
    result->SetRow(row_index1, temp_row);
    return(result);
}

template <class T>
RectangleMatrix<T>* SwapColumn(RectangleMatrix<T>* matrix, int col_index1, int col_index2)
{
    RectangleMatrix<T>* result = new RectangleMatrix<T>(matrix);
    T temp_elem1, temp_elem2;
    for (int ii = 0; ii < matrix->GetHeight(); ii++)
    {
        temp_elem1 = matrix->GetElem(ii, col_index1);
        temp_elem2 = matrix->GetElem(ii, col_index2);
        result->SetElem(ii, col_index1, temp_elem2);
        result->SetElem(ii, col_index2, temp_elem1);
    }
    return(result);
}

template <class T>
double FindNorm(RectangleMatrix<T>* matrix)
{
    double row_sum, max_sum;
    max_sum = 0;
    for (int ii = 0; ii < matrix->GetHeight(); ii++)
    {
        row_sum = 0;
        for (int ii2 = 0; ii2 < matrix->GetWidth(); ii2++)
        {
            row_sum = row_sum + Module(matrix->GetElem(ii, ii2));
        }
        if (max_sum < row_sum)
        {
            max_sum = row_sum;
        }
    }
    return(max_sum);
}

#endif