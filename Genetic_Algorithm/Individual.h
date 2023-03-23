#pragma once
#include <vector>
#include <random>
#include "Problem.h"

class Individual
{
public:
	Individual();
	Individual(int numberOfGenes);
	Individual(int numberOfGenes, std::mt19937& gen, std::uniform_int_distribution<>& dist);
	void updateFitness(const Problem& problem);
	void mutate(double mutProb, std::mt19937& gen, std::uniform_real_distribution<>& dist);
	std::vector <Individual> crossover(const Individual& other, std::mt19937& gen, std::uniform_int_distribution<>& dist);
	int getFitness();
	void showGenom();

private:
	std::vector<int> genes;
	int fitness;

};
