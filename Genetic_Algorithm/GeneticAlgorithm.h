#pragma once
#include <iostream>
#include <random>
#include "KnapsackProblem.h"
#include "Individual.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm(KnapsackProblem& problem);
	int configurateAlgorithm(int populationSize, double crossoverRate, double mutationRate, int numGenerations);
	Individual chooseParent(std::mt19937& gen, std::uniform_int_distribution<>& disPopulation);
	void createPopulation(std::mt19937& gen, std::uniform_int_distribution<>& dis);
	Individual evolve();
	void updateBestSolution(Individual& individual);

private:
	KnapsackProblem problem;
	std::vector<Individual> population;
	Individual bestIndividual;
	int population_size;
	double crossover_rate;
	double mutation_rate;
	int num_generations;

};