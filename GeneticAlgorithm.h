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
	int iSetProperties(int iPopSize, double dCrossProb, double dMutProb, KnapsackProblem<T> * pcProblem);
	int iRunFor(int iIterations);
	Individual<T> * cGetBestIndividual();
	Individual<T> * cGetBestFromAllPopulations();
	double dGetRandomCrossProb();
	void vDeletePopulation();
	
private:
	void vCalculatePopulationFittness();
	void vPerformCrossing();
	void vPerformMutation();
	void vRunIteration();
	void vCreatePopulation();
	void vSaveBestFromPopulation();
	void vChooseParents(Individual<T>** pcParent1,Individual<T>** pcParent2);
	void vCrossAndAdd(Individual<T>* pcParent1, Individual<T>* pcParent2,std::vector<Individual<T>*>* pvNewPopVec);
	int iGetRandomIndividualNumber();
	void vShowPopulation();
	KnapsackProblem<T> * pc_problem;
	std::vector<Individual<T>*>*  pv_populationVector;
	int i_populationSize;
	double d_crossingProbabilty;
	double d_mutationProbability;
	Individual<T>  * c_bestIndividual;
	std::random_device c_randomDevice;
	std::mt19937 c_randomGenerator;
	std::uniform_int_distribution<> c_intDistribution;
	std::uniform_real_distribution<> c_realDistribution;
	 

	
	
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