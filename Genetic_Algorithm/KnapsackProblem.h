#pragma once
#include "Problem.h"

class KnapsackProblem : public Problem
{
public:

    struct Item
    {
        int value;
        int weight;
        Item(int item_value, int item_weight)
        {
            value = item_value;
            weight = item_weight;
        }
    };

    KnapsackProblem();
    int readProblemFromFile(std::string name) override;
    int fitness(std::vector<int>& solution) const override;
    int configureProblem(int nr_of_items, int maximum_weight, std::vector<Item>& vector_of_items);
    int getNumberOfItems();

private:
    int number_of_items;
    int max_weight;
    std::vector<Item> items;
};
