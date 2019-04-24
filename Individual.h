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

	void vCalculateFittness(KnapsackProblem<T> * pcProblem);
	void vTryToMutate();
	void vShowGenotype();
	void vCreateGenotype();
	void vCreateGenotype(std::vector<Item>* pvItems);
	double dGetFittness(); 
	std::vector<T> & vGetGenotype();
	Individual<T> & operator++();
	Individual<T> & operator++(int);
	Individual<T>  operator+(const Individual<T> & cOther);


private:
	double dGetRandomProbability();
	int iGetCuttingPoint();
	void vMutate();

	std::vector<T> genotype;
	std::vector<Item> * v_itemsVector;
	int i_genotypeSize;
	double d_fittness;
	double d_mutationProbalility;
	double d_crossingProbability;
	std::random_device c_randomDevice;
	std::mt19937  c_randomGenerator;
	std::uniform_real_distribution<>c_realDistribution;
	std::uniform_int_distribution<>c_intDistribution;

	



	
};

static const std::string SPACE = " ";
template class Individual<bool>;
template class Individual<int>;
template class Individual<double>;