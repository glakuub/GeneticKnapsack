#include "GeneticAlgorithm.h"



template <class T> GeneticAlgorithm<T>::GeneticAlgorithm() :randomGenerator(randomDevice()), realDistribution(0,1)
{
	populationSize = 0;
	crossingProbabilty = 0;
	mutationProbability = 0;
	knapsackProblem = nullptr;
	populationVector = nullptr;
	bestIndividual = nullptr;

}

template <class T> GeneticAlgorithm<T>::~GeneticAlgorithm()
{
    deletePopulation();
	
}

template <class T> int GeneticAlgorithm<T>::setParameters(int iPopSize, double dCrossProb, double dMutProb,
                                                          KnapsackProblem<T> *pcProblem)
{	
	if (iPopSize < 1)return ERR_POP_SIZE_LESS_THAN_ONE;
	populationSize = iPopSize;
	intDistribution=std::uniform_int_distribution<>(0, iPopSize - 1);

	if (1 < dCrossProb || dCrossProb < 0)return ERR_INCORRECT_CROSS_PROB;
	crossingProbabilty = dCrossProb;

	if (1 < dMutProb || dMutProb < 0)return ERR_INCORRECT_MUT_PROB;
	mutationProbability = dMutProb;
	if (pcProblem == nullptr) return ERR_PROBLEM_POINTER_IS_NULL;
	knapsackProblem = pcProblem;
	return 1;
}

template <> void GeneticAlgorithm<bool>::createPopulation()
{	
	
	populationVector = new std::vector<Individual<bool>*>();
	for (int ii = 0; ii < populationSize; ii++)
	{
		populationVector->push_back(new Individual<bool>(knapsackProblem->getItemsNumber(), knapsackProblem->getItemsVector(), mutationProbability, crossingProbabilty));
        populationVector->at(ii)->createGenotype();
	}
}

template <> void GeneticAlgorithm<int>::createPopulation()
{

	populationVector = new std::vector<Individual<int>*>();
	for (int ii = 0; ii < populationSize; ii++)
	{
		populationVector->push_back(new Individual<int>(knapsackProblem->getItemsNumber(), knapsackProblem->getItemsVector(), mutationProbability, crossingProbabilty));
        populationVector->at(ii)->createGenotype(knapsackProblem->getItemsVector());
	}
}

template <> void GeneticAlgorithm<double>::createPopulation()
{

	populationVector = new std::vector<Individual<double>*>();
	for (int ii = 0; ii < populationSize; ii++)
	{
		populationVector->push_back(new Individual<double>(knapsackProblem->getItemsNumber(), knapsackProblem->getItemsVector(), mutationProbability, crossingProbabilty));
        populationVector->at(ii)->createGenotype(knapsackProblem->getItemsVector());
	}
}

template <class T> void GeneticAlgorithm<T>::showPopulation()
{
	for (int ii = 0; ii < populationSize; ii++)
	{
		populationVector->at(ii)->showGenotype();
		std::cout<<"val: " << populationVector->at(ii)->getFittness()<< std::endl;
	}
}

template <class T> void GeneticAlgorithm<T>::runIteration()
{

    calculatePopulationFittness();
    saveBestFromPopulation();
    performCrossing();
    performMutation();
	
	
	
}

template <class T> void GeneticAlgorithm<T>::saveBestFromPopulation()
{
	Individual<T> * c_best = getBestIndividual();
	if (bestIndividual == nullptr || c_best->getFittness() >= bestIndividual->getFittness())
	{
		if (bestIndividual != nullptr)delete bestIndividual;
		bestIndividual = new Individual<T>(*c_best);
	}
}

template <class T> Individual<T> * GeneticAlgorithm<T>::getBestIndividual()
{
	Individual<T> * pc_toReturn=nullptr;
	
	for (int ii = 0; ii < populationSize; ii++)
	{
		if (pc_toReturn == nullptr || populationVector->at(ii)->getFittness() >= pc_toReturn->getFittness())
		{
			pc_toReturn = populationVector->at(ii);
			
		}
	}
	return pc_toReturn;
}

template <class T> Individual<T> * GeneticAlgorithm<T>::getBestFromAllPopulations()
{
	return bestIndividual;
}

template <class T> int GeneticAlgorithm<T>::runFor(int iSeconds)
{	
	if (knapsackProblem != nullptr)
	{
		
		if (iSeconds>0)
		{	
			std::clock_t begin = clock();
            createPopulation();
			while ((double(clock()-begin)/ CLOCKS_PER_SEC )<iSeconds)
			{
                runIteration();

			}
            calculatePopulationFittness();
		}
		else
		{
			return ERR_INCORRECT_ITER_NUM;
		}

		

		return 1;
	}
	else
	{
		return ERR_PROBLEM_NOT_FOUND;
	}
	
}

template <class T> void GeneticAlgorithm<T>::calculatePopulationFittness()
{
	for (int ii = 0; ii < populationSize; ii++)
	{
		populationVector->at(ii)->calculateFittness(knapsackProblem);
	}
}

template <class T> int GeneticAlgorithm<T>::getRandomIndividualNumber()
{
	return intDistribution(randomGenerator);
}

template <class T> void GeneticAlgorithm<T>::chooseParents(Individual<T> **pcParent1, Individual<T> **pcParent2)
{
	
	int i_parent1Cand1 = getRandomIndividualNumber();
	int i_parent1Cand2 = getRandomIndividualNumber();

	int i_parent2Cand1 = getRandomIndividualNumber();
	int i_parent2Cand2 = getRandomIndividualNumber();

	if (populationVector->at(i_parent1Cand1)->getFittness() >= populationVector->at(i_parent1Cand2)->getFittness())
	{
		*pcParent1 = populationVector->at(i_parent1Cand1);
	}
	else
	{
		*pcParent1 = populationVector->at(i_parent1Cand2);
	}

	if (populationVector->at(i_parent2Cand1)->getFittness() >= populationVector->at(i_parent2Cand2)->getFittness())
	{
		*pcParent2 = populationVector->at(i_parent2Cand1);
	}
	else
	{
		*pcParent2 = populationVector->at(i_parent2Cand2);
	}

}

template <class T> void GeneticAlgorithm<T>::crossAndAdd(Individual<T> *pcParent1, Individual<T> *pcParent2,
                                                         std::vector<Individual<T> *> *pvNewPopVec)
{		

	Individual<T> * pc_child1;
	Individual<T> * pc_child2;

	if (getRandomCrossProb() < crossingProbabilty)
	{
		pc_child1 = new Individual<T>(*pcParent1 + *pcParent2);
		pc_child2 = new Individual<T>(*pcParent1 + *pcParent2);
		pvNewPopVec->push_back(pc_child1);
		pvNewPopVec->push_back(pc_child2);
	}
	else
	{	
		
		pc_child1 = new Individual<T>(*pcParent1);
		pc_child2 = new Individual<T>(*pcParent2);
		pvNewPopVec->push_back(pc_child1);
		pvNewPopVec->push_back(pc_child2);
		
	}
}
template <class T> void GeneticAlgorithm<T>::performCrossing()
{
	auto newPopulationVector = new std::vector<Individual<T>*>;
	

	while (newPopulationVector->size() < populationSize)
	{
		Individual<T> * pc_parent1;
		Individual<T> * pc_parent2;

        chooseParents(&pc_parent1, &pc_parent2);
        crossAndAdd(pc_parent1, pc_parent2, newPopulationVector);
	
	}

	for (int ii = 0; ii < populationSize; ii++)
	{
		delete populationVector->at(ii);
	}
	delete populationVector;
	populationVector = newPopulationVector;
	newPopulationVector = nullptr;

}
template <class T> void GeneticAlgorithm<T>::performMutation()
{	
	for (int ii = 0; ii < populationSize; ii++)
	{	
		(*populationVector->at(ii))++;
	}
}

template <class T> double GeneticAlgorithm<T>::getRandomCrossProb()
{	

	return realDistribution(randomGenerator);
}
template <class T> void GeneticAlgorithm<T>::deletePopulation()
{
	if (populationVector != nullptr)
	{
		for (int ii = 0; ii < populationSize; ii++)
		{
			delete populationVector->at(ii);
		}
		delete populationVector;
	}
}

