#ifndef DRAWMATRIX_H
#define DRAWMATRIX_H

#include "RectangleMatrix.h"
#include "MatrKnap.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void DrawMatrix (RenderWindow* window, RectangleMatrix<int>* matrix, int x1, int y1, int x2, int y2)
{
	int height = matrix->GetHeight();
	int width = matrix->GetWidth();
	int size;
	if (height > width)
	{
		size = (x2 - x1) / height;
	}
	else
	{
		size = (x2 - x1) / width;
	}
	for (int ii = 0; ii < height; ii++)
	{
		for (int ii2 = 0; ii2 < width; ii2++)
		{
			CircleShape square(size - 20, 4);
			square.setPosition(x1 + ii2 * (size), y1 + ii * (size));
			square.setOutlineThickness(10.f);
			square.setOutlineColor(Color::Black);
			square.rotate(45.f);
			if (matrix->GetElem(ii, ii2) != 0)
			{
				if (matrix->GetElem(ii, ii2) == 1)
				{
					square.setFillColor(Color::Red);
				}
				else if (matrix->GetElem(ii, ii2) == 2)
				{
					square.setFillColor(Color::Green);
				}
				else if (matrix->GetElem(ii, ii2) == 3)
				{
					square.setFillColor(Color::Yellow);
				}
				else if (matrix->GetElem(ii, ii2) == 4)
				{
					square.setFillColor(Color::Blue);
				}
				else
				{
					square.setFillColor(Color::Cyan);
				}
				(*window).draw(square);
			}
			else
			{
				square.setFillColor(Color::White);
				(*window).draw(square);
			}
		}
	}
}

#endif