//
// Created by jakub on 24.04.19.
//
#include "KnapsackProblem.h"
#include "GeneticAlgorithm.h"
#include "Individual.h"
#include "Item.h"
#include  <vector>

static const int ITEMS_NUMBER = 10;
int main()
{

    std::vector<Item> itemsVector;
    for(int index=0;index<ITEMS_NUMBER;index++)
    {
        itemsVector.push_back(Item(ITEMS_NUMBER-index,index,index));
    }

    KnapsackProblem<double> knapsackProblem;
    knapsackProblem.setParameters(10, 10, &itemsVector);
    GeneticAlgorithm<double> geneticAlgorithm;
    geneticAlgorithm.setParameters(200, 0.5, 0.5, &knapsackProblem);
    geneticAlgorithm.runFor(10);
    Individual<double> * bestIndividual;


    bestIndividual = geneticAlgorithm.getBestFromAllPopulations();
    bestIndividual->showGenotype();
    bestIndividual->calculateFittness(&knapsackProblem);
    std::cout<<std::endl;
    std::cout<< bestIndividual->getFittness()<<std::endl;
    return 0;
}