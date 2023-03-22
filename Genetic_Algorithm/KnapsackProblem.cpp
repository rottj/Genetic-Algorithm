#include "KnapsackProblem.h"
#include "Errors.h"
#include <iostream>
#include <fstream>
#include <sstream>

KnapsackProblem::KnapsackProblem()
{
	number_of_items = 0;
	max_weight = 0;
}

int KnapsackProblem::readProblemFromFile(std::string name)
{
	std::ifstream myfile(name);
	std::string line;

	if (myfile.is_open())
	{
		getline(myfile, line);
		try {
			number_of_items = std::stoi(line);
		}
		catch (const std::invalid_argument& ia) {
			return INVALID_TYPE_IN_FILE;
		}

		if (number_of_items <= 0)
		{
			return WRONG_NUMBER_OF_ITEMS;
		}

		getline(myfile, line);
		try {
			max_weight = std::stoi(line);
		}
		catch (const std::invalid_argument& ia) {
			return INVALID_TYPE_IN_FILE;
		}

		if (max_weight <= 0)
		{
			return WRONG_MAX_WEIGHT;
		}

		for (int i = 0; i < number_of_items; i++)
		{
			if (getline(myfile, line))
			{
				std::stringstream ss(line);
				std::string str_value, str_weight;
				int value, weight;

				ss >> str_value >> str_weight;
				try {
					value = std::stoi(str_value);
					weight = std::stoi(str_weight);
					if (value < 0)
					{
						return NEGATIVE_VALUE_OF_ITEM;
					}
					if (weight < 0)
					{
						return NEGATIVE_WEIGHT_OF_ITEM;
					}
					items.push_back(Item(value, weight));
				}
				catch (std::invalid_argument& ia)
				{
					return INVALID_TYPE_IN_FILE;
				}

			}
			else
			{
				return NOT_ENOUGHT_ITEMS_IN_FILE;
			}
		}
	}
	else
	{
		return FILE_NOT_OPEN;
	}

	myfile.close();
	return SUCCESS;
}

int KnapsackProblem::configureProblem(int nr_of_items, int maximum_weight, std::vector<Item>& vector_of_items)
{
	if (nr_of_items <= 0)
	{
		return WRONG_NUMBER_OF_ITEMS;
	}
	number_of_items = nr_of_items;

	if (maximum_weight <= 0)
	{
		return WRONG_MAX_WEIGHT;
	}
	max_weight = maximum_weight;

	if (vector_of_items.size() != number_of_items)
	{
		return DIFFERENT_VECTOR_SIZE_THEN_EXPECTED;
	}
	for (int i = 0; i < vector_of_items.size(); i++)
	{
		if (vector_of_items[i].weight < 0)
		{
			return NEGATIVE_WEIGHT_OF_ITEM;
		}

		if (vector_of_items[i].value < 0)
		{
			return NEGATIVE_VALUE_OF_ITEM;
		}
	}
	items = vector_of_items;
	return SUCCESS;
}

int KnapsackProblem::fitness(std::vector<int>& solution) const
{
	int value = 0;
	int weight = 0;

	for (int i = 0; i < solution.size(); i++)
	{
		if (solution[i] == 1)
		{
			value += items[i].value;
			weight += items[i].weight;
		}
	}

	if (weight > max_weight) value = 0;
	return value;
}

int KnapsackProblem::getNumberOfItems()
{
	return number_of_items;
}
