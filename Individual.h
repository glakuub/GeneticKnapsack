#pragma once
#include <random>
#include <string>
#include <iostream>
#include <vector>
#include "KnapsackProblem.h"


template <class T>
class Individual
{
public:
	
	Individual(int iGenotypeSize,std::vector<Item> * pcItems, double dMutProb, double dCrossProb);
	Individual(const Individual& cOther);
	~Individual();

	void calculateFittness(KnapsackProblem<T> *knapsackProblem);
	void tryToMutate();
	void showGenotype();
	void createGenotype();
	void createGenotype(std::vector<Item> *pvItems);
	double getFittness();
	std::vector<T> & getGenotype();
	Individual<T> & operator++();
	Individual<T> & operator++(int);
	Individual<T>  operator+(const Individual<T> & other);


private:
	double getRandomProbability();
	int getCuttingPoint();
	void mutate();

	std::vector<T> genotypeVector;
	std::vector<Item> * itemsVector;
	int genotypeSize;
	double fittness;
	double mutationProbalility;
	double crossingProbability;
	std::random_device randomDevice;
	std::mt19937  randomGenerator;
	std::uniform_real_distribution<> realDistribution;
	std::uniform_int_distribution<> intDistribution;

	



	
};

static const std::string SPACE = " ";
template class Individual<bool>;
template class Individual<int>;
template class Individual<double>;