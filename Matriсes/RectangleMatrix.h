#ifndef RECTANGLEMATRIX_H
#define RECTANGLEMATRIX_H

#include <iostream>
#include <iomanip>
#include <string>
#include "BasicStructures/DynamicArray.h"
#include "BasicStructures/Sequence.h"
#include "BasicStructures/ArraySequence.h"


template <class T>
class RectangleMatrix
{
private:
    ArraySequenceMut<ArraySequenceMut<T>*>* matrix;
    int height;
    int width;

public:
    RectangleMatrix()
    {
        width = 1;
        height = 1;
        ArraySequenceMut<T>** row_array = new ArraySequenceMut<T>*[height];
        for (int ii = 0; ii < height; ii++)
        {
            row_array[ii] = new ArraySequenceMut<T>(width);
        }
        matrix = new ArraySequenceMut<ArraySequenceMut<T>*>(row_array, height);
        delete row_array;
    }

    RectangleMatrix(int row_number, int col_number)
    {
        width = col_number;
        height = row_number;
        ArraySequenceMut<T>** row_array = new ArraySequenceMut<T>*[height];
        for (int ii = 0; ii < height; ii++)
        {
            row_array[ii] = new ArraySequenceMut<T>(width);
        }
        matrix = new ArraySequenceMut<ArraySequenceMut<T>*>(row_array, height);

        for (int ii = 0; ii < height; ii++)
        {
            for (int ii2 = 0; ii2 < width; ii2++)
            {
                SetElem(ii, ii2, T());
            }
        }
        delete row_array;
    }

    RectangleMatrix(int row_number, int col_number, T* items)
    {
        width = col_number;
        height = row_number;
        ArraySequenceMut<T>** row_array = new ArraySequenceMut<T>*[height];
        for (int ii = 0; ii < height; ii++)
        {
            row_array[ii] = new ArraySequenceMut<T>(width);
        }
        matrix = new ArraySequenceMut<ArraySequenceMut<T>*>(row_array, height);

        for (int ii = 0; ii < height; ii++)
        {
            for (int ii2 = 0; ii2 < width; ii2++)
            {
                SetElem(ii, ii2, items[ii * width + ii2]);
            }
        }
        delete row_array;
    }

    RectangleMatrix(ArraySequenceMut<ArraySequenceMut<T>*>* items)
    {
        height = items->GetLength();
        width = items->Get(0)->GetLength();
        matrix = items;
    }

    RectangleMatrix(RectangleMatrix* other_matrix)
    {
        width = other_matrix->width;
        height = other_matrix->height;
        ArraySequenceMut<T>** row_array = new ArraySequenceMut<T>*[height];
        for (int ii = 0; ii < height; ii++)
        {
            row_array[ii] = new ArraySequenceMut<T>(width);
        }
        matrix = new ArraySequenceMut<ArraySequenceMut<T>*>(row_array, height);

        T temp_elem;
        for (int ii = 0; ii < height; ii++)
        {
            for (int ii2 = 0; ii2 < width; ii2++)
            {
                temp_elem = other_matrix->GetElem(ii, ii2);
                this->SetElem(ii, ii2, temp_elem);
            }
        }
        delete row_array;
    }

    RectangleMatrix(const RectangleMatrix& other_matrix)
    {
        width = other_matrix.width;
        height = other_matrix.height;
        ArraySequenceMut<T>** row_array = new ArraySequenceMut<T>*[height];
        for (int ii = 0; ii < height; ii++)
        {
            row_array[ii] = new ArraySequenceMut<T>(width);
        }
        matrix = new ArraySequenceMut<ArraySequenceMut<T>*>(row_array, height);

        T temp_elem;
        for (int ii = 0; ii < height; ii++)
        {
            for (int ii2 = 0; ii2 < width; ii2++)
            {
                temp_elem = other_matrix.GetElem(ii, ii2);
                this->SetElem(ii, ii2, temp_elem);
            }
        }
        delete row_array;
    }

    RectangleMatrix(RectangleMatrix&& other_matrix)
    {
        width = other_matrix.width;
        height = other_matrix.height;
        matrix = other_matrix.matrix;
        other_matrix.width = 0;
        other_matrix.height = 0;
        other_matrix.matrix = nullptr;
    }

    RectangleMatrix& operator = (const RectangleMatrix& other_matrix)
    {
        delete matrix;
        width = other_matrix.width;
        height = other_matrix.height;
        ArraySequenceMut<T>** row_array = new ArraySequenceMut<T>*[height];
        for (int ii = 0; ii < height; ii++)
        {
            row_array[ii] = new ArraySequenceMut<T>(width);
        }
        matrix = new ArraySequenceMut<ArraySequenceMut<T>*>(row_array, height);

        T temp_elem;
        for (int ii = 0; ii < height; ii++)
        {
            for (int ii2 = 0; ii2 < width; ii2++)
            {
                temp_elem = other_matrix.GetElem(ii, ii2);
                this->SetElem(ii, ii2, temp_elem);
            }
        }
        return *this;
    }

    RectangleMatrix& operator = (RectangleMatrix* other_matrix)
    {
        delete matrix;
        width = other_matrix->width;
        height = other_matrix->height;
        ArraySequenceMut<T>** row_array = new ArraySequenceMut<T>*[height];
        for (int ii = 0; ii < height; ii++)
        {
            row_array[ii] = new ArraySequenceMut<T>(width);
        }
        matrix = new ArraySequenceMut<ArraySequenceMut<T>*>(row_array, height);

        T temp_elem;
        for (int ii = 0; ii < height; ii++)
        {
            for (int ii2 = 0; ii2 < width; ii2++)
            {
                temp_elem = other_matrix->GetElem(ii, ii2);
                this->SetElem(ii, ii2, temp_elem);
            }
        }
        return *this;
    }

    RectangleMatrix& operator = (RectangleMatrix&& other_matrix)
    {
        delete matrix;
        width = other_matrix.width;
        height = other_matrix.height;
        matrix = other_matrix.matrix;
        other_matrix.width = 0;
        other_matrix.height = 0;
        other_matrix.matrix = nullptr;
        return *this;
    }

    ~RectangleMatrix()
    {
        if (matrix != nullptr)
        {
            for (int ii = 0; ii < height; ii++)
            {
                delete matrix->Get(ii);
            }
            delete matrix;
        }
    }

    ArraySequenceMut<T>* GetRow(int row_index) const
    {
        if (row_index < 0 || row_index >= height)
        {
            throw std::out_of_range("Error: Height index out of range\n");
        }
        return(matrix->Get(row_index));
    }

    T GetElem(int height_index, int width_index) const
    {
        if (width_index < 0 || width_index >= width)
        {
            throw std::out_of_range("Error: Width index out of range\n");
        }
        if (height_index < 0 || height_index >= height)
        {
            throw std::out_of_range("Error: Height index out of range\n");
        }
        return(matrix->Get(height_index)->Get(width_index));
    }

    int GetHeight() const
    {
        return(height);
    }

    int GetWidth() const
    {
        return(width);
    }

    RectangleMatrix<T>* GetSubMatrix(int row1, int row2, int col1, int col2) const
    {
        if (col1 < 0 || col2 < 0 || col1 >= width || col2 >= width || col1 > col2)
        {
            throw std::out_of_range("Error: Width index out of range\n");
        }
        if (row1 < 0 || row2 < 0 || row1 >= height || row2 >= height || row1 > row2)
        {
            throw std::out_of_range("Error: Height index out of range\n");
        }
        int new_row = row2 - row1 + 1;
        int new_col = col2 - col1 + 1;
        RectangleMatrix<T>* sub_matrix = new RectangleMatrix<T>(new_row, new_col);
        for (int ii = row1; ii <= row2; ii++)
        {
            for (int jj = col1; jj <= col2; jj++)
            {
                sub_matrix->SetElem(ii - row1, jj - col1, this->GetElem(ii, jj));
            }
        }
        return sub_matrix;
    }

    void SetElem(int height_index, int width_index, const T& item)
    {
        if (width_index < 0 || width_index >= width)
        {
            throw std::out_of_range("Error: Width index out of range\n");
        }
        if (height_index < 0 || height_index >= height)
        {
            throw std::out_of_range("Error: Height index out of range\n");
        }
        matrix->Get(height_index)->Set(item, width_index);
    }

    void SetRow(int row_index, ArraySequenceMut<T>* row)
    {
        if (row_index < 0 || row_index >= height)
        {
            throw std::out_of_range("Error: Height index out of range\n");
        }
        matrix->Set(row, row_index);
    }
};

template <class T>
std::ostream& operator << (std::ostream& stream, const RectangleMatrix<T>& matrix)
{
    for (int ii = 0; ii < matrix.GetHeight(); ii++)
    {
        for (int ii2 = 0; ii2 < matrix.GetWidth(); ii2++)
        {
            stream << std::setw(2) << matrix.GetElem(ii, ii2) << " ";
        }
        stream << std::endl;
    }
    return stream;
}

template <class T>
std::ostream& operator << (std::ostream& stream, RectangleMatrix<T>* matrix)
{
    for (int ii = 0; ii < matrix->GetHeight(); ii++)
    {
        for (int ii2 = 0; ii2 < matrix->GetWidth(); ii2++)
        {
            stream << std::setw(2) << matrix->GetElem(ii, ii2) << " ";
        }
        stream << std::endl;
    }
    return stream;
}

template <class T>
std::string ToString(const RectangleMatrix<T>& matrix)
{
    std::string stream;
    for (int ii = 0; ii < matrix.GetHeight(); ii++)
    {
        for (int ii2 = 0; ii2 < matrix.GetWidth(); ii2++)
        {
            stream = stream + std::to_string(matrix.GetElem(ii, ii2)) + " ";
        }
        stream = stream + "\n";
    }
    return stream;
}

template <class T>
std::string ToString(RectangleMatrix<T>* matrix)
{
    std::string stream;
    for (int ii = 0; ii < matrix->GetHeight(); ii++)
    {
        for (int ii2 = 0; ii2 < matrix->GetWidth(); ii2++)
        {
            stream = stream + std::to_string(matrix->GetElem(ii, ii2)) + " ";
        }
        stream = stream + "\n";
    }
    return stream;
}

template <class T>
bool operator == (const RectangleMatrix<T>& matr1, const RectangleMatrix<T>& matr2)
{
    if (matr1.GetHeight() != matr2.GetHeight())
    {
        return 0;
    }
    if (matr1.GetWidth() != matr2.GetWidth())
    {
        return 0;
    }
    else
    {
        for (int ii = 0; ii < matr1.GetHeight(); ii++)
        {
            for (int ii2 = 0; ii2 < matr1.GetWidth(); ii2++)
            {
                if (matr1.GetElem(ii, ii2) != matr2.GetElem(ii, ii2))
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

template <class T>
bool operator != (const RectangleMatrix<T>& matr1, const RectangleMatrix<T>& matr2)
{
    if (matr1.GetHeight() != matr2.GetHeight())
    {
        return 1;
    }
    if (matr1.GetWidth() != matr2.GetWidth())
    {
        return 1;
    }
    else
    {
        for (int ii = 0; ii < matr1.GetHeight(); ii++)
        {
            for (int ii2 = 0; ii2 < matr1.GetWidth(); ii2++)
            {
                if (matr1.GetElem(ii, ii2) != matr2.GetElem(ii, ii2))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

#endif