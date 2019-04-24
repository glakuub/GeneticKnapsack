#include "CGeneticAlgorithm.h"



template <class T> CGeneticAlgorithm<T>::CGeneticAlgorithm() :c_randomGenerator(c_randomDevice()), c_realDistribution(0,1)
{
	i_populationSize = 0;
	d_crossingProbabilty = 0;
	d_mutationProbability = 0;
	pc_problem = nullptr;
	pv_populationVector = nullptr;
	c_bestIndividual = nullptr;

}

template <class T> CGeneticAlgorithm<T>::~CGeneticAlgorithm()
{	
	vDeletePopulation();
	
}

template <class T> int CGeneticAlgorithm<T>::iSetProperties(int iPopSize, double dCrossProb, double dMutProb, CKnapsackProblem<T>* pcProblem)
{	
	if (iPopSize < 1)return ERR_POP_SIZE_LESS_THAN_ONE;
	i_populationSize = iPopSize;
	c_intDistribution=std::uniform_int_distribution<>(0, iPopSize - 1);

	if (1 < dCrossProb || dCrossProb < 0)return ERR_INCORRECT_CROSS_PROB;
	d_crossingProbabilty = dCrossProb;

	if (1 < dMutProb || dMutProb < 0)return ERR_INCORRECT_MUT_PROB;
	d_mutationProbability = dMutProb;
	if (pcProblem == nullptr) return ERR_PROBLEM_POINTER_IS_NULL;
	pc_problem = pcProblem;
	return 1;
}

template <> void CGeneticAlgorithm<bool>::vCreatePopulation()
{	
	
	pv_populationVector = new std::vector<CIndividual<bool>*>();
	for (int ii = 0; ii < i_populationSize; ii++)
	{
		pv_populationVector->push_back(new CIndividual<bool>(pc_problem->iGetItemsNumber(),pc_problem->pvGetItems(), d_mutationProbability, d_crossingProbabilty));
		pv_populationVector->at(ii)->vCreateGenotype();
	}
}

template <> void CGeneticAlgorithm<int>::vCreatePopulation()
{

	pv_populationVector = new std::vector<CIndividual<int>*>();
	for (int ii = 0; ii < i_populationSize; ii++)
	{
		pv_populationVector->push_back(new CIndividual<int>(pc_problem->iGetItemsNumber(), pc_problem->pvGetItems(), d_mutationProbability, d_crossingProbabilty));
		pv_populationVector->at(ii)->vCreateGenotype(pc_problem->pvGetItems());
	}
}

template <> void CGeneticAlgorithm<double>::vCreatePopulation()
{

	pv_populationVector = new std::vector<CIndividual<double>*>();
	for (int ii = 0; ii < i_populationSize; ii++)
	{
		pv_populationVector->push_back(new CIndividual<double>(pc_problem->iGetItemsNumber(), pc_problem->pvGetItems(), d_mutationProbability, d_crossingProbabilty));
		pv_populationVector->at(ii)->vCreateGenotype(pc_problem->pvGetItems());
	}
}

template <class T> void CGeneticAlgorithm<T>::vShowPopulation()
{
	for (int ii = 0; ii < i_populationSize; ii++)
	{
		pv_populationVector->at(ii)->vShowGenotype();
		std::cout<<"val: " << pv_populationVector->at(ii)->dGetFittness()<< std::endl;
	}
}

template <class T> void CGeneticAlgorithm<T>::vRunIteration()
{	
	
	vCalculatePopulationFittness();
	vSaveBestFromPopulation();
	vPerformCrossing();
	vPerformMutation();
	
	
	
}

template <class T> void CGeneticAlgorithm<T>::vSaveBestFromPopulation()
{
	CIndividual<T> * c_best = cGetBestIndividual();
	if (c_bestIndividual == nullptr || c_best->dGetFittness() >= c_bestIndividual->dGetFittness())
	{
		if (c_bestIndividual != nullptr)delete c_bestIndividual;
		c_bestIndividual = new CIndividual<T>(*c_best);
	}
}

template <class T> CIndividual<T> * CGeneticAlgorithm<T>::cGetBestIndividual()
{
	CIndividual<T> * pc_toReturn=nullptr;
	
	for (int ii = 0; ii < i_populationSize; ii++)
	{
		if (pc_toReturn == nullptr || pv_populationVector->at(ii)->dGetFittness() >= pc_toReturn->dGetFittness())
		{
			pc_toReturn = pv_populationVector->at(ii);
			
		}
	}
	return pc_toReturn;
}

template <class T> CIndividual<T> * CGeneticAlgorithm<T>::cGetBestFromAllPopulations()
{
	return c_bestIndividual;
}

template <class T> int CGeneticAlgorithm<T>::iRunFor(int iSeconds)
{	
	if (pc_problem != nullptr)
	{
		
		if (iSeconds>0)
		{	
			std::clock_t begin = clock();
			vCreatePopulation();
			while ((double(clock()-begin)/ CLOCKS_PER_SEC )<iSeconds)
			{
				vRunIteration();

			}
			vCalculatePopulationFittness();
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

template <class T> void CGeneticAlgorithm<T>::vCalculatePopulationFittness()
{
	for (int ii = 0; ii < i_populationSize; ii++)
	{
		pv_populationVector->at(ii)->vCalculateFittness(pc_problem);
	}
}

template <class T> int CGeneticAlgorithm<T>::iGetRandomIndividualNumber()
{
	return c_intDistribution(c_randomGenerator);
}

template <class T> void CGeneticAlgorithm<T>::vChooseParents(CIndividual<T>** pcParent1, CIndividual<T>** pcParent2)
{
	
	int i_parent1Cand1 = iGetRandomIndividualNumber();
	int i_parent1Cand2 = iGetRandomIndividualNumber();

	int i_parent2Cand1 = iGetRandomIndividualNumber();
	int i_parent2Cand2 = iGetRandomIndividualNumber();

	if (pv_populationVector->at(i_parent1Cand1)->dGetFittness() >= pv_populationVector->at(i_parent1Cand2)->dGetFittness())
	{
		*pcParent1 = pv_populationVector->at(i_parent1Cand1);
	}
	else
	{
		*pcParent1 = pv_populationVector->at(i_parent1Cand2);
	}

	if (pv_populationVector->at(i_parent2Cand1)->dGetFittness() >= pv_populationVector->at(i_parent2Cand2)->dGetFittness())
	{
		*pcParent2 = pv_populationVector->at(i_parent2Cand1);
	}
	else
	{
		*pcParent2 = pv_populationVector->at(i_parent2Cand2);
	}

}

template <class T> void CGeneticAlgorithm<T>::vCrossAndAdd(CIndividual<T>* pcParent1, CIndividual<T>* pcParent2, std::vector<CIndividual<T>*>* pvNewPopVec)
{		

	CIndividual<T> * pc_child1;
	CIndividual<T> * pc_child2;

	if (dGetRandomCrossProb() < d_crossingProbabilty)
	{
		pc_child1 = new CIndividual<T>(*pcParent1 + *pcParent2);
		pc_child2 = new CIndividual<T>(*pcParent1 + *pcParent2);
		pvNewPopVec->push_back(pc_child1);
		pvNewPopVec->push_back(pc_child2);
	}
	else
	{	
		
		pc_child1 = new CIndividual<T>(*pcParent1);
		pc_child2 = new CIndividual<T>(*pcParent2);
		pvNewPopVec->push_back(pc_child1);
		pvNewPopVec->push_back(pc_child2);
		
	}
}
template <class T> void CGeneticAlgorithm<T>::vPerformCrossing()
{
	std::vector<CIndividual<T>*>* pv_newPopulationVector = new std::vector<CIndividual<T>*>;
	

	while (pv_newPopulationVector->size() < i_populationSize)
	{
		CIndividual<T> * pc_parent1;
		CIndividual<T> * pc_parent2;
		
		vChooseParents(&pc_parent1, &pc_parent2);
		vCrossAndAdd(pc_parent1, pc_parent2, pv_newPopulationVector);
	
	}

	for (int ii = 0; ii < i_populationSize; ii++)
	{
		delete pv_populationVector->at(ii);
	}
	delete pv_populationVector;
	pv_populationVector = pv_newPopulationVector;
	pv_newPopulationVector = nullptr;

}
template <class T> void CGeneticAlgorithm<T>::vPerformMutation()
{	
	for (int ii = 0; ii < i_populationSize; ii++)
	{	
		(*pv_populationVector->at(ii))++;
	}
}

template <class T> double CGeneticAlgorithm<T>::dGetRandomCrossProb()
{	

	return c_realDistribution(c_randomGenerator);
}
template <class T> void CGeneticAlgorithm<T>::vDeletePopulation()
{
	if (pv_populationVector != nullptr)
	{
		for (int ii = 0; ii < i_populationSize; ii++)
		{
			delete pv_populationVector->at(ii);
		}
		delete pv_populationVector;
	}
}

