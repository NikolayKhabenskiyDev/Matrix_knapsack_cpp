#ifndef	GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include "GraphicButtons.h"
#include "DrawMatrix.h"

using namespace std;
using namespace form;
using namespace sf;

int GUI()
{
	bool got_max_weight = false;
	bool got_height = false;
	bool got_width = false;
	bool got_amount = false;
	bool got_item_height = false;
	bool got_item_width = false;
	bool got_weight = false;
	bool got_value = false;
	bool got_matrix = false;
	bool created_items = false;
	bool created_knapsack = false;

	int max_weight = 0;
	int height = 0;
	int width = 0;
	int item_height = 0;
	int item_width = 0;
	int amount = 0;
	int item_weight = 0;
	int item_value = 0;
	int iterator = 0;
	RectangleMatrix<int>* item_matrix = nullptr;
	ArraySequenceMut<MatrKnapItem*>* items = nullptr;
	ArraySequenceMut<MatrKnapContent*>* knapsacks = nullptr;

	RenderWindow window(sf::VideoMode(1200, 1200), "Form");

	Label label(700, 30, "Max weight of Knapsack:");
	Input input(700, 60, 200, 30);
	Button button(700, 100, 50, 30, "Enter");

	Label label1(700, 150, "Height of Knapsack:");
	Input input1(700, 180, 200, 30);
	Button button1(700, 220, 50, 30, "Enter");

	Label label2(700, 270, "Width of Knapsack:");
	Input input2(700, 300, 200, 30);
	Button button2(700, 340, 50, 30, "Enter");

	Label label3(30, 30, "Amount of Items:");
	Input input3(30, 60, 200, 30);
	Button button3(30, 100, 50, 30, "Enter");

	Label extra_label(30, 180, "");

	Label label6(30, 230, "Weight of Item:");
	Input input6(30, 260, 200, 30);
	Button button6(30, 300, 50, 30, "Enter");

	Label label7(30, 350, "Value of Item:");
	Input input7(30, 380, 200, 30);
	Button button7(30, 420, 50, 30, "Enter");

	Label label4(30, 470, "Height of Item:");
	Input input4(30, 500, 200, 30);
	Button button4(30, 540, 50, 30, "Enter");

	Label label5(30, 590, "Width of Item:");
	Input input5(30, 620, 200, 30);
	Button button5(30, 660, 50, 30, "Enter");

	Label label8(30, 740, "Matrix of Item:");
	Button button8(30, 780, 140, 30, "Create random");
	Label extra_label2(30, 830, "Patterns:");
	Button button8_1(30, 880, 70, 90, "1.xxxx\n  xxxx\n  xxxx\n  xxxx");
	Button button8_2(110, 880, 70, 90, "2.xxxx\n  x00x\n  x00x\n  xxxx");
	Button button8_3(190, 880, 70, 90, "3.x0x0\n  0x0x\n  x0x0\n  0x0x");
	Button button8_4(30, 970, 70, 90, "4.0x0x\n  x0x0\n  0x0x\n  x0x0");
	Button button8_5(110, 970, 70, 90, "5.xxxx\n  0xxx\n  00xx\n  000x");
	Button button8_6(190, 970, 70, 90, "6.x000\n  xx00\n  xxx0\n  xxxx");

	Label label9(200, 750, "Created Items:\n");
	Button button9(700, 400, 250, 30, "FIND BEST KNAPSACK");
	Label label10(900, 900, "");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Vector2i mouse = Mouse::getPosition(window);

					if (button.select(mouse) && got_max_weight == false)
					{
						max_weight = atoi(input.readText().c_str());
						if (max_weight >= 1)
						{
							label.text = "Max weight of Knapsack:" + input.readText();
							got_max_weight = true;
						}
						else
						{
							label.text = "Max weight of Knapsack: Error";
						}
					}
					if (button1.select(mouse) && got_height == false)
					{
						height = atoi(input1.readText().c_str());
						if (height >= 1)
						{
							label1.text = "Height of Knapsack:" + input1.readText();
							got_height = true;
						}
						else
						{
							label1.text = "Height of Knapsack: Error";
						}
					}
					if (button2.select(mouse) && got_width == false) 
					{
						width = atoi(input2.readText().c_str());
						if (width >= 1)
						{
							label2.text = "Width of Knapsack:" + input2.readText();
							got_width = true;
						}
						else
						{
							label2.text = "Width of Knapsack: Error";
						}
					}
					if (button3.select(mouse) && got_amount == false)
					{
						amount = atoi(input3.readText().c_str());
						if (amount >= 1)
						{
							items = new ArraySequenceMut<MatrKnapItem*>(amount);
							label3.text = "Amount of Items:" + input3.readText();
							extra_label.text = "Item" + to_string(iterator + 1) + " of " + to_string(amount);
							got_amount = true;
						}
						else
						{
							label3.text = "Amount of Items: Error";
						}
					}
					if (button4.select(mouse) && got_amount && got_item_height == false && amount >iterator)
					{
						item_height = atoi(input4.readText().c_str());
						if (item_height >= 1)
						{
							label4.text = "Height of Item:" + input4.readText();
							got_item_height = true;
						}
						else
						{
							label4.text = "Height of Item: Error";
						}
					}
					if (button5.select(mouse) && got_amount && got_item_width == false && amount > iterator)
					{
						item_width = atoi(input5.readText().c_str());
						if (item_width >= 1)
						{
							label5.text = "Width of Item:" + input5.readText();
							got_item_width = true;
						}
						else
						{
							label5.text = "Width of Item: Error";
						}
					}
					if (button6.select(mouse) && got_amount && got_weight == false && amount > iterator)
					{
						item_weight = atoi(input6.readText().c_str());
						if (item_weight >= 1)
						{
							label6.text = "Weight of Item:" + input6.readText();
							got_weight = true;
						}
						else
						{
							label6.text = "Weight of Item: Error";
						}
					}
					if (button7.select(mouse) && got_amount && got_value == false && amount > iterator)
					{
						item_value = atoi(input7.readText().c_str());
						if (item_value >= 1)
						{
							label7.text = "Value of Item:" + input7.readText();
							got_value = true;
						}
						else
						{
							label7.text = "Value of Item: Error";
						}
					}
					if (button8.select(mouse) && got_amount && got_item_height && got_item_width && got_matrix == false && amount > iterator)
					{
						item_matrix = MatrixGen(item_height, item_width, iterator + 1);
						got_matrix = true;
					}
					if (button8_1.select(mouse) && got_amount && got_item_height && got_item_width && got_matrix == false && amount > iterator)
					{
						item_matrix = CreateMatrixPatternFull(item_height, item_width, iterator + 1);
						got_matrix = true;
					}
					if (button8_2.select(mouse) && got_amount && got_item_height && got_item_width && got_matrix == false && amount > iterator)
					{
						item_matrix = CreateMatrixPatternBorder(item_height, item_width, iterator + 1);
						got_matrix = true;
					}
					if (button8_3.select(mouse) && got_amount && got_item_height && got_item_width && got_matrix == false && amount > iterator)
					{
						item_matrix = CreateMatrixPatternChessOrder1(item_height, item_width, iterator + 1);
						got_matrix = true;
					}
					if (button8_4.select(mouse) && got_amount && got_item_height && got_item_width && got_matrix == false && amount > iterator)
					{
						item_matrix = CreateMatrixPatternChessOrder2(item_height, item_width, iterator + 1);
						got_matrix = true;
					}
					if (button8_5.select(mouse) && got_amount && got_item_height && got_item_width && got_matrix == false && amount > iterator)
					{
						item_matrix = CreateMatrixPatternTriangleUp(item_height, item_width, iterator + 1);
						got_matrix = true;
					}
					if (button8_6.select(mouse) && got_amount && got_item_height && got_item_width && got_matrix == false && amount > iterator)
					{
						item_matrix = CreateMatrixPatternTriangleDown(item_height, item_width, iterator + 1);
						got_matrix = true;
					}
					if (button9.select(mouse) && got_height && got_width && got_max_weight && created_items && created_knapsack == false)
					{
						knapsacks = MatrKnapProblem(items, amount, max_weight, height, width);
						label10.text = "Knapsack weight:" + to_string(knapsacks->GetFirst()->GetWeight())
							+ "\nKnapsack value:" + to_string(knapsacks->GetFirst()->GetValue());
						created_knapsack = true;

					}
					input.select(mouse);
					input1.select(mouse);
					input2.select(mouse);
					input3.select(mouse);
					input4.select(mouse);
					input5.select(mouse);
					input6.select(mouse);
					input7.select(mouse);
				}
			}
			if (event.type == sf::Event::TextEntered)
			{
				if (input.select())
				{
					input.reText(event.text.unicode);
				}
				if (input1.select())
				{
					input1.reText(event.text.unicode);
				}
				if (input2.select())
				{
					input2.reText(event.text.unicode);
				}
				if (input3.select())
				{
					input3.reText(event.text.unicode);
				}
				if (input4.select() && got_amount)
				{
					input4.reText(event.text.unicode);
				}
				if (input5.select() && got_amount)
				{
					input5.reText(event.text.unicode);
				}
				if (input6.select() && got_amount)
				{
					input6.reText(event.text.unicode);
				}
				if (input7.select() && got_amount)
				{
					input7.reText(event.text.unicode);
				}

			}
		}

		window.clear(Color::White);

		window.draw(label.displayText());
		window.draw(label1.displayText());
		window.draw(label2.displayText());
		window.draw(label3.displayText());

		window.draw(button.displayButton());
		window.draw(button.displayText());

		window.draw(button1.displayButton());
		window.draw(button1.displayText());

		window.draw(button2.displayButton());
		window.draw(button2.displayText());

		window.draw(button3.displayButton());
		window.draw(button3.displayText());

		window.draw(input.displayButton());
		window.draw(input.displayText());

		window.draw(input1.displayButton());
		window.draw(input1.displayText());

		window.draw(input2.displayButton());
		window.draw(input2.displayText());

		window.draw(input3.displayButton());
		window.draw(input3.displayText());

		if (got_amount)
		{
			window.draw(extra_label.displayText());
			window.draw(label4.displayText());
			window.draw(label5.displayText());
			window.draw(label6.displayText());
			window.draw(label7.displayText());
			window.draw(label9.displayText());

			window.draw(button4.displayButton());
			window.draw(button4.displayText());

			window.draw(button5.displayButton());
			window.draw(button5.displayText());

			window.draw(button6.displayButton());
			window.draw(button6.displayText());

			window.draw(button7.displayButton());
			window.draw(button7.displayText());

			window.draw(input4.displayButton());
			window.draw(input4.displayText());

			window.draw(input5.displayButton());
			window.draw(input5.displayText());

			window.draw(input6.displayButton());
			window.draw(input6.displayText());

			window.draw(input7.displayButton());
			window.draw(input7.displayText());
		}
		if (got_amount && got_item_height && got_item_width)
		{
			window.draw(extra_label2.displayText());
			window.draw(label8.displayText());

			window.draw(button8.displayButton());
			window.draw(button8.displayText());

			window.draw(button8_1.displayButton());
			window.draw(button8_1.displayText());

			window.draw(button8_2.displayButton());
			window.draw(button8_2.displayText());

			window.draw(button8_3.displayButton());
			window.draw(button8_3.displayText());

			window.draw(button8_4.displayButton());
			window.draw(button8_4.displayText());

			window.draw(button8_5.displayButton());
			window.draw(button8_5.displayText());

			window.draw(button8_6.displayButton());
			window.draw(button8_6.displayText());
		}
		if (got_amount && got_item_height && got_item_width && got_weight && got_value && got_matrix && amount > iterator)
		{
			MatrKnapItem* current_item = new MatrKnapItem(to_string(iterator), item_weight, item_value, item_matrix);
			items->Append(current_item);

			got_item_height = false;
			got_item_width = false;
			got_weight = false;
			got_value = false;
			got_matrix = false;

			if (iterator + 2 <= amount)
			{
				extra_label.text = "Item" + to_string(iterator + 2) + " of " + to_string(amount);
			}
			label4.text = "Height of Item:";
			input4.text = "";
			label5.text = "Width of Item:";
			input5.text = "";
			label6.text = "Weight of Item:";
			input6.text = "";
			label7.text = "Value of Item:";
			input7.text = "";
			label8.text = "Matrix of Item:";
			label9.text = label9.text + "Item " + to_string(iterator + 1) + "- Weight "
				+ to_string(item_weight) + "; Value " + to_string(item_value) + "\n";

			iterator++;
		}
		if (iterator > 0)
		{
			for (int ii = 0; ii < iterator; ii++)
			{
				DrawMatrix(&window, items->Get(ii)->GetMatr(), 350, 100 + ii * 1.2 * 350 / amount,
					350 + 350 / amount, 100 + (ii + 1) * 1.2 * 350 / amount);
			}
		}
		if (got_amount && iterator == amount && created_items == false)
		{
			label9.text = label9.text + "All items created";
			created_items = true;
		}
		if (created_items && got_height && got_width && got_max_weight)
		{
			window.draw(button9.displayButton());
			window.draw(button9.displayText());
		}
		if (created_items && got_height && got_width && got_max_weight && created_knapsack)
		{
			DrawMatrix(&window, knapsacks->GetFirst()->GetMatr(), 700, 450, 1000, 750);
			window.draw(label10.displayText());
		}
		window.display();
		sleep(milliseconds(1000 / 60));
	}
	delete knapsacks;
	delete items;
	return 0;
}


#endif