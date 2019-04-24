#pragma once
#include <random>
#include <string>
#include <iostream>
#include <vector>
#include "CKnapsackProblem.h"


template <class T>
class CIndividual
{
public:
	
	CIndividual(int iGenotypeSize,std::vector<CItem> * pcItems, double dMutProb, double dCrossProb);
	CIndividual(const CIndividual& cOther);
	~CIndividual();

	void vCalculateFittness(CKnapsackProblem<T> * pcProblem);
	void vTryToMutate();
	void vShowGenotype();
	void vCreateGenotype();
	void vCreateGenotype(std::vector<CItem>* pvItems);
	double dGetFittness(); 
	std::vector<T> & vGetGenotype();
	CIndividual<T> & operator++();
	CIndividual<T> & operator++(int);
	CIndividual<T>  operator+(const CIndividual<T> & cOther);


private:
	double dGetRandomProbability();
	int iGetCuttingPoint();
	void vMutate();

	std::vector<T> genotype;
	std::vector<CItem> * v_itemsVector;
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
template class CIndividual<bool>;
template class CIndividual<int>;
template class CIndividual<double>;