#pragma once
#include "Individual.h"
#include <vector>
#include <iostream>
#include <ctime>

template <class T>
class GeneticAlgorithm
{
public:
	GeneticAlgorithm();
	~GeneticAlgorithm();
	int setParameters(int iPopSize, double dCrossProb, double dMutProb, KnapsackProblem<T> *pcProblem);
	int runFor(int iIterations);
	Individual<T> * getBestIndividual();
	Individual<T> * getBestFromAllPopulations();
	double getRandomCrossProb();
	void deletePopulation();
	
private:
	void calculatePopulationFittness();
	void performCrossing();
	void performMutation();
	void runIteration();
	void createPopulation();
	void saveBestFromPopulation();
	void chooseParents(Individual<T> **pcParent1, Individual<T> **pcParent2);
	void crossAndAdd(Individual<T> *pcParent1, Individual<T> *pcParent2, std::vector<Individual<T> *> *pvNewPopVec);
	int getRandomIndividualNumber();
	void showPopulation();
	KnapsackProblem<T> * knapsackProblem;
	std::vector<Individual<T>*>*  populationVector;
	int populationSize;
	double crossingProbabilty;
	double mutationProbability;
	Individual<T>  * bestIndividual;
	std::random_device randomDevice;
	std::mt19937 randomGenerator;
	std::uniform_int_distribution<> intDistribution;
	std::uniform_real_distribution<> realDistribution;
	 

	
	
	static const int ERR_POP_SIZE_LESS_THAN_ONE = -1;
	static const int ERR_INCORRECT_CROSS_PROB = -2;
	static const int ERR_INCORRECT_MUT_PROB = -3;
	static const int ERR_PROBLEM_POINTER_IS_NULL = -4;
	static const int ERR_PROBLEM_NOT_FOUND = -5;
	static const int ERR_INCORRECT_ITER_NUM = -6;
	
	
};

template class GeneticAlgorithm<bool>;
template class GeneticAlgorithm<int>;
template class GeneticAlgorithm<double>;