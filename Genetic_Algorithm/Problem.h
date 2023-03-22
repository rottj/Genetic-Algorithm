#pragma once
#include <string>
#include <vector>

class Problem {
public:
	virtual int readProblemFromFile(std::string name) = 0;
	virtual int fitness(std::vector<int>& solution) const = 0;
};
