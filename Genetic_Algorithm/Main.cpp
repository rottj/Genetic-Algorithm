#include "GeneticAlgorithm.h"
#include "Errors.h"
#include <iostream>

void test_from_file(std::string name)
{
	KnapsackProblem problem;
	int result = problem.readProblemFromFile(name);
	if (result == SUCCESS)
	{
		GeneticAlgorithm ga(problem);
		Individual best = ga.evolve();
		std::cout << best.getFitness();
		std::cout << std::endl;
		best.showGenom();
	}
	else if (result == WRONG_NUMBER_OF_ITEMS)
	{
		std::cout << "WRONG_NUMBER_OF_ITEMS";
	}
	else if (result == WRONG_MAX_WEIGHT)
	{
		std::cout << "WRONG_MAX_WEIGHT";
	}
	else if (result == FILE_NOT_OPEN)
	{
		std::cout << "FILE_NOT_OPEN";
	}
	else if (result == NOT_ENOUGHT_ITEMS_IN_FILE)
	{
		std::cout << "NOT_ENOUGHT_ITEMS_IN_FILE";
	}
	else if (result == NEGATIVE_VALUE_OF_ITEM)
	{
		std::cout << "NEGATIVE_VALUE_OF_ITEM";
	}
	else if (result == NEGATIVE_WEIGHT_OF_ITEM)
	{
		std::cout << "NEGATIVE_WEIGHT_OF_ITEM";
	}
	else if (result == INVALID_TYPE_IN_FILE)
	{
		std::cout << "INVALID_TYPE_IN_FILE";
	}

}

void test(int numberOfItems, int maxWeight, std::vector<KnapsackProblem::Item>& vector, int populationSize, double crossoverRate, double mutationRate, int numGenerations)
{
	KnapsackProblem problem;
	int result_1 = problem.configureProblem(numberOfItems, maxWeight, vector);
	if (result_1 == SUCCESS)
	{
		GeneticAlgorithm ga(problem);
		int result_2 = ga.configurateAlgorithm(populationSize, crossoverRate, mutationRate, numGenerations);
		if (result_2 == SUCCESS)
		{
			Individual best = ga.evolve();
			std::cout << best.getFitness();
			std::cout << std::endl;
			best.showGenom();
		}
		else if (result_2 == NEGATIVE_POPULATION_SIZE)
		{
			std::cout << "NEGATIVE_POPULATION_SIZE";
		}
		else if (result_2 == ODD_POPULATION_SIZE)
		{
			std::cout << "ODD_POPULATION_SIZE";
		}
		else if (result_2 == WRONG_CROSSOVER_RATE)
		{
			std::cout << "WRONG_CROSSOVER_RATE";
		}
		else if (result_2 == WRONG_MUTATION_RATE)
		{
			std::cout << "WRONG_MUTATION_RATE";
		}
		else if (result_2 == NEGATIVE_NUMBER_OF_GENERATIONS)
		{
			std::cout << "NEGATIVE_NUMBER_OF_GENERATIONS";
		}
	}

	else if (result_1 == WRONG_NUMBER_OF_ITEMS)
	{
		std::cout << "WRONG_NUMBER_OF_ITEMS";
	}
	else if (result_1 == WRONG_MAX_WEIGHT)
	{
		std::cout << "NEGATIVE_MAX_WEIGHT";
	}
	else if (result_1 == DIFFERENT_VECTOR_SIZE_THEN_EXPECTED)
	{
		std::cout << "DIFFERENT_VECTOR_SIZE_THEN_EXPECTED";
	}
	else if (result_1 == NEGATIVE_VALUE_OF_ITEM)
	{
		std::cout << "NEGATIVE_VALUE_OF_ITEM";
	}
	else if (result_1 == NEGATIVE_WEIGHT_OF_ITEM)
	{
		std::cout << "NEGATIVE_WEIGHT_OF_ITEM";
	}
}

int main()
{
	std::vector<KnapsackProblem::Item> vector = { {2, 3}, {3, 4}, {4, 5}, {5, 8}, {9, 10} };
	int numberOfItems = 5;
	int maxWeight = 20;
	int populationSize = 100;
	double crossoverRate = 0.6;
	double mutationRate = 0.01;
	int numGenerations = 200;

	test(numberOfItems, maxWeight, vector, populationSize, crossoverRate, mutationRate, numGenerations); // should return 16, 01101
	std::cout << std::endl << "--------------------------" << std::endl;
	test_from_file("test.txt"); // should return 150, 110010
}
