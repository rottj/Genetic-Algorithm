#include "Individual.h"
#include <random>
#include <iostream>


Individual::Individual()
{
	fitness = -1;
}

Individual::Individual(int numberOfGenes)
{
	fitness = 0;
	genes.resize(numberOfGenes);
}

Individual::Individual(int numberOfGenes, std::mt19937& gen, std::uniform_int_distribution<>& dist)
{
	fitness = 0;
	genes.resize(numberOfGenes);

	for (int i = 0; i < numberOfGenes; i++)
	{
		genes[i] = dist(gen);
	}
}

void Individual::updateFitness(const Problem& problem)
{
	fitness = problem.fitness(genes);
}

void Individual::mutate(double mutProb, std::mt19937& gen, std::uniform_real_distribution<>& dist)
{
	for (int i = 0; i < genes.size(); i++)
	{
		if (dist(gen) < mutProb)
		{
			genes[i] = 1 - genes[i];
		}
	}
}

std::vector <Individual> Individual::crossover(const Individual& other, std::mt19937& gen, std::uniform_int_distribution<>& dist)
{
	int crossoverPoint = dist(gen);

	std::vector <Individual> children(2);
	children[0] = Individual(genes.size());
	children[1] = Individual(genes.size());

	for (int i = 0; i < crossoverPoint; i++)
	{
		children[0].genes[i] = (genes[i]);
		children[1].genes[i] = (other.genes[i]);
	}
	for (int i = crossoverPoint; i < genes.size(); i++)
	{
		children[0].genes[i] = (other.genes[i]);
		children[1].genes[i] = (genes[i]);
	}

	return children;
}

int Individual::getFitness()
{
	return fitness;
}

void Individual::showGenom()
{
	for (int i = 0; i < genes.size(); i++)
	{
		std::cout << genes[i];
	}
}
