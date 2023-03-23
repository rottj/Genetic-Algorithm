#include "GeneticAlgorithm.h"
#include "Errors.h"
#include <random>
#include <iostream>

const int POPULATION_SIZE = 250;
const double CROSSOVER_RATE = 0.6;
const double MUTATION_RATE = 0.01;
const int NUM_GENERATIONS = 1000;

GeneticAlgorithm::GeneticAlgorithm(KnapsackProblem& knapsackProblem)
{
	population_size = POPULATION_SIZE;
	crossover_rate = CROSSOVER_RATE;
	mutation_rate = MUTATION_RATE;
	num_generations = NUM_GENERATIONS;
	problem = knapsackProblem;
}

void GeneticAlgorithm::createPopulation(std::mt19937& gen, std::uniform_int_distribution<>& dis)
{
	population.resize(population_size);

	for (int i = 0; i < population_size; i++) {
		population[i] = (Individual(problem.getNumberOfItems(), gen, dis));
		population[i].updateFitness(problem);
		updateBestSolution(population[i]);
	}
}

Individual GeneticAlgorithm::chooseParent(std::mt19937& gen, std::uniform_int_distribution<>& disPopulation)
{

	Individual individual_1 = population[disPopulation(gen)];
	Individual individual_2 = population[disPopulation(gen)];

	if (individual_1.getFitness() > individual_2.getFitness())
	{
		return individual_1;
	}
	else
	{
		return individual_2;
	}
}

Individual GeneticAlgorithm::evolve()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> disProb(0, 1);
	std::uniform_int_distribution<> disPopulation(0, population_size - 1);
	std::uniform_int_distribution<> disGenom(0, 1);
	std::uniform_int_distribution<> disCrossoverPoint(0, (problem.getNumberOfItems() - 1));

	Individual individual_1;
	Individual individual_2;
	std::vector<Individual> children;
	std::vector<Individual> result_crossover;

	createPopulation(gen, disGenom);

	for (int generation = 0; generation < num_generations; generation++)
	{
		for (int i = 0; i < population_size / 2; i++)
		{
			individual_1 = chooseParent(gen, disPopulation);
			individual_2 = chooseParent(gen, disPopulation);
			if (disProb(gen) < crossover_rate)
			{
				result_crossover = individual_1.crossover(individual_2, gen, disCrossoverPoint);
				individual_1 = result_crossover[0];
				individual_2 = result_crossover[1];
			}

			individual_1.mutate(mutation_rate, gen, disProb);
			individual_2.mutate(mutation_rate, gen, disProb);
			individual_1.updateFitness(problem);
			individual_2.updateFitness(problem);

			updateBestSolution(individual_1);
			updateBestSolution(individual_2);

			children.push_back(individual_1);
			children.push_back(individual_2);

		}

		population = children;
		children.clear();
	}

	return bestIndividual;
}

int GeneticAlgorithm::configurateAlgorithm(int populationSize, double crossoverRate, double mutationRate, int numGenerations)
{
	if (populationSize <= 0)
	{
		return NEGATIVE_POPULATION_SIZE;
	}

	if (populationSize % 2 != 0)
	{
		return ODD_POPULATION_SIZE;
	}
	population_size = populationSize;

	if (crossoverRate < 0 || crossoverRate > 1)
	{
		return WRONG_CROSSOVER_RATE;
	}
	crossover_rate = crossoverRate;

	if (mutationRate < 0 || mutationRate > 1)
	{
		return WRONG_MUTATION_RATE;

	}
	mutation_rate = mutationRate;

	if (numGenerations < 0)
	{
		return NEGATIVE_NUMBER_OF_GENERATIONS;
	}
	num_generations = numGenerations;

	return SUCCESS;
}

void GeneticAlgorithm::updateBestSolution(Individual& individual)
{
	if (individual.getFitness() > bestIndividual.getFitness())
	{
		bestIndividual = individual;
	}
}

