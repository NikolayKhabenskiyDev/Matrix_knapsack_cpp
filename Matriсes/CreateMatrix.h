#ifndef MATRIXCREATION_H
#define MATRIXCREATION_H 

#include "BasicStructures/Pointers.h"
#include "Interfaces/SafeInput.h"
#include "BasicStructures/DynamicArray.h"
#include "BasicStructures/Sequence.h"
#include "BasicStructures/ArraySequence.h"
#include "RectangleMatrix.h"

RectangleMatrix<int>* CreateMatrixPatternFull(int height, int width, int content_elem)
{
	RectangleMatrix<int>* matr = new RectangleMatrix<int>(height, width);
	for (int ii = 0; ii < height; ii++)
	{
		for (int ii2 = 0; ii2 < width; ii2++)
		{
			matr->SetElem(ii, ii2, content_elem);
		}
	}
	return matr;
}

RectangleMatrix<int>* CreateMatrixPatternBorder(int height, int width, int content_elem)
{
	RectangleMatrix<int>* matr = new RectangleMatrix<int>(height, width);
	for (int ii = 0; ii < height; ii++)
	{
		matr->SetElem(ii, 0, content_elem);
	}
	for (int ii = 0; ii < width; ii++)
	{
		matr->SetElem(0, ii, content_elem);
	}
	for (int ii = 0; ii < height; ii++)
	{
		matr->SetElem(ii, width - 1, content_elem);
	}
	for (int ii = 0; ii < width; ii++)
	{
		matr->SetElem(height - 1, ii, content_elem);
	}
	return matr;
}

RectangleMatrix<int>* CreateMatrixPatternChessOrder1(int height, int width, int content_elem)
{
	RectangleMatrix<int>* matr = new RectangleMatrix<int>(height, width);
	for (int ii = 0; ii < height; ii++)
	{
		for (int ii2 = 0; ii2 < width; ii2++)
		{
			if ((ii + ii2) % 2 == 0)
			{
				matr->SetElem(ii, ii2, content_elem);
			}
		}
	}
	return matr;
}

RectangleMatrix<int>* CreateMatrixPatternChessOrder2(int height, int width, int content_elem)
{
	RectangleMatrix<int>* matr = new RectangleMatrix<int>(height, width);
	for (int ii = 0; ii < height; ii++)
	{
		for (int ii2 = 0; ii2 < width; ii2++)
		{
			if ((ii + ii2) % 2 == 1)
			{
				matr->SetElem(ii, ii2, content_elem);
			}
		}
	}
	return matr;
}

RectangleMatrix<int>* CreateMatrixPatternTriangleUp(int height, int width, int content_elem)
{
	RectangleMatrix<int>* matr = new RectangleMatrix<int>(height, width);
	for (int ii = 0; ii < height; ii++)
	{
		for (int ii2 = ii; ii2 < width; ii2++)
		{
			matr->SetElem(ii, ii2, content_elem);
		}
	}
	return matr;
}

RectangleMatrix<int>* CreateMatrixPatternTriangleDown(int height, int width, int content_elem)
{
	RectangleMatrix<int>* matr = new RectangleMatrix<int>(height, width);
	for (int ii = 0; ii < height; ii++)
	{
		for (int ii2 = 0; ii2 <= ii && ii2 < width; ii2++)
		{
			matr->SetElem(ii, ii2, content_elem);
		}
	}
	return matr;
}

RectangleMatrix<int>* CreateMatrixChoosePattern(int height, int width, int content_elem)
{
	RectangleMatrix<int>* matr = nullptr;
	std::cout << "Choose one of pattern" << "\n"
		"1.xxxx  2.xxxx  3.x0x0  4.0x0x  5.xxxx  6.x000" << "\n"
		"  xxxx    x00x    0x0x    x0x0    0xxx    xx00" << "\n"
		"  xxxx    x00x    x0x0    0x0x    00xx    xxx0" << "\n"
		"  xxxx    xxxx    0x0x    x0x0    000x    xxxx" << "\n";
	int pattern = get_int();
	while (pattern < 1 || pattern > 6)
	{
		std::cout << "Choose correct number" << "\n";
		pattern = get_int();
	}

	if (pattern == 1)
	{
		matr = CreateMatrixPatternFull(height, width, content_elem);
	}
	if (pattern == 2)
	{
		matr = CreateMatrixPatternBorder(height, width, content_elem);
	}
	if (pattern == 3)
	{
		matr = CreateMatrixPatternChessOrder1(height, width, content_elem);
	}
	if (pattern == 4)
	{
		matr = CreateMatrixPatternChessOrder2(height, width, content_elem);
	}
	if (pattern == 5)
	{
		matr = CreateMatrixPatternTriangleUp(height, width, content_elem);
	}
	if (pattern == 6)
	{
		matr = CreateMatrixPatternTriangleDown(height, width, content_elem);
	}
	return matr;
}

#endif