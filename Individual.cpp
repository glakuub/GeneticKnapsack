#include "Individual.h"



template <class T> Individual<T>::Individual(int iGenotypeSize, std::vector<Item> * pcItems, double dMutProb, double dCrossProb) : randomGenerator(randomDevice()), realDistribution(0,1), intDistribution(0, iGenotypeSize -1)
{	
	genotypeSize = iGenotypeSize;
	fittness = 0;
	itemsVector = pcItems;
	crossingProbability = dCrossProb;
	mutationProbalility = dMutProb;
}
template <class T> Individual<T> ::Individual(const Individual& cOther) :randomGenerator(randomDevice()), realDistribution(0, 1), intDistribution(0, cOther.genotypeSize - 1)
{	
	itemsVector = cOther.itemsVector;
	genotypeSize = cOther.genotypeSize;
	fittness = cOther.fittness;
	genotypeVector = cOther.genotypeVector;
	crossingProbability = cOther.crossingProbability;
	mutationProbalility = cOther.mutationProbalility;
	
}
template <class T> std::vector<T>& Individual<T>::getGenotype()
{
	return genotypeVector;
}
template <class T> Individual<T>::~Individual()=default;

template <class T>  Individual<T> & Individual<T>::operator++ ()
{
    mutate();
	return *this;
}
template <class T>  Individual<T> & Individual<T>::operator++ (int)
{
    mutate();
	return *this;
}
template <class T>  Individual<T> Individual<T>::operator+ (const Individual<T> & other)
{
	Individual<T>  pc_child(genotypeSize,itemsVector,mutationProbalility,crossingProbability);

	int i_cuttingPoint = getCuttingPoint();
	for (int ii = 0; ii < i_cuttingPoint; ii++)
	{
        pc_child.getGenotype().push_back(genotypeVector.at(ii));
		
	}
	for (int ii = i_cuttingPoint; ii < genotypeSize; ii++)
	{
        pc_child.getGenotype().push_back(other.genotypeVector.at(ii));
	}
	
	return pc_child;
}
template <> void Individual<int>::createGenotype(std::vector<Item> *pvItems)
{
	if (genotypeVector.empty())
	{	
		

		for (int ii = 0; ii < genotypeSize; ii++)
		{	
			std::uniform_int_distribution<>c_intDistribution(0, pvItems->at(ii).howManyCanGet());
			int i_gene = c_intDistribution(randomGenerator);
			genotypeVector.push_back(i_gene);
		}
	}
}
template <> void Individual<double>::createGenotype(std::vector<Item> *pvItems)
{
	if (genotypeVector.empty())
	{	
		

		for (int ii = 0; ii < genotypeSize; ii++)
		{	
			std::uniform_real_distribution<>c_realDistribution(0, pvItems->at(ii).howManyCanGet());
			double d_gene = c_realDistribution(randomGenerator);
			genotypeVector.push_back(d_gene);
		}
	}
}
template<> void Individual<bool>::createGenotype()
{
	if (genotypeVector.empty())
	{	
		
		std::uniform_int_distribution<>c_intDistribution(0, 1);
		for (int ii = 0; ii < genotypeSize; ii++)
		{	
			bool b_gene = c_intDistribution(randomGenerator);
			genotypeVector.push_back(b_gene);
		}
	}
}




template <class T> void Individual<T>::showGenotype()
{	

	if (!genotypeVector.empty())
	{	
	
		std::cout << std::endl;
		for (int ii = 0; ii < genotypeSize; ii++)
		{
			std::cout << genotypeVector.at(ii) <<SPACE;
		}
	}
	
}

template <class T> void Individual<T>::calculateFittness(KnapsackProblem<T> *knapsackProblem)
{	
	fittness = knapsackProblem->calculateFitness(genotypeVector);
	
}



template <class T> void Individual<T>::tryToMutate()
{
	if (getRandomProbability() < mutationProbalility)
	{
		(*this)++;
	}
}

template <> void Individual<bool>::mutate()
{		

	for (int ii = 0; ii < genotypeVector.size(); ii++)
	{
		if (getRandomProbability() < mutationProbalility)
		{
			genotypeVector.at(ii) = !genotypeVector.at(ii);
		}
	}
	/*
		int i_firstCut = iGetCuttingPoint();
		if (i_firstCut == 0)i_firstCut++;
		int i_secondCut = 0;
		do {
			i_secondCut = getCuttingPoint();
		} while (i_firstCut == i_secondCut || i_secondCut == 0);

		if (i_secondCut < i_firstCut)
		{
			int temp = i_secondCut;
			i_secondCut = i_firstCut;
			i_firstCut = temp;
		}
		for (int ii = 0; ii <= (i_secondCut - i_firstCut) / 2; ii++)
		{
			std::swap(genotypeVector.at(i_firstCut+ii), genotypeVector.at(i_secondCut - ii));
		}
		*/
}
template <> void Individual<int>::mutate()
{
	for (int ii = 0; ii < genotypeVector.size(); ii++)
	{	
		if (getRandomProbability() < mutationProbalility)
		{	
			if (getRandomProbability() < mutationProbalility)
			{
				int d_howMany = itemsVector->at(ii).howManyCanGet();
				int d_mutationRange = d_howMany / 2;

				std::uniform_int_distribution<> c_mutationValue(-d_mutationRange, d_mutationRange);
				genotypeVector.at(ii) = genotypeVector.at(ii) + c_mutationValue(randomGenerator);
				if (genotypeVector.at(ii) > d_howMany)
				{
					genotypeVector.at(ii) = d_howMany;
				}
				if (genotypeVector.at(ii) < 0)
				{
					genotypeVector.at(ii) = 0;
				}

			}
			genotypeVector.at(ii) = itemsVector->at(ii).howManyCanGet() - genotypeVector.at(ii);
		}
	}
	/*
	int i_firstCut = iGetCuttingPoint();
	if (i_firstCut == 0)i_firstCut++;
	int i_secondCut = 0;
	do {
		i_secondCut = getCuttingPoint();
	} while (i_firstCut == i_secondCut || i_secondCut == 0);

	if (i_secondCut < i_firstCut)
	{
		int temp = i_secondCut;
		i_secondCut = i_firstCut;
		i_firstCut = temp;
	}
	for (int ii = 0; ii <= (i_secondCut - i_firstCut) / 2; ii++)
	{
		std::swap(genotypeVector.at(i_firstCut + ii), genotypeVector.at(i_secondCut - ii));
	}
	*/
}
template <> void Individual<double>::mutate()
{
	for (int ii = 0; ii < genotypeVector.size(); ii++)
	{
		if (getRandomProbability() < mutationProbalility)
		{	
			double d_howMany = itemsVector->at(ii).howManyCanGet();
			double d_mutationRange = d_howMany/10.0;

			std::uniform_real_distribution<> c_mutationValue(-d_mutationRange, d_mutationRange);
			genotypeVector.at(ii) = genotypeVector.at(ii) + c_mutationValue(randomGenerator);
			if (genotypeVector.at(ii) > d_howMany)
			{
				genotypeVector.at(ii) = d_howMany;
			}
			if (genotypeVector.at(ii) < 0)
			{
				genotypeVector.at(ii) = 0;
			}
			
			
		}
	}
	/*
	int i_firstCut = iGetCuttingPoint();
	if (i_firstCut == 0)i_firstCut++;
	int i_secondCut = 0;
	do {
		i_secondCut = getCuttingPoint();
	} while (i_firstCut == i_secondCut || i_secondCut == 0);

	if (i_secondCut < i_firstCut)
	{
		int temp = i_secondCut;
		i_secondCut = i_firstCut;
		i_firstCut = temp;
	}
	for (int ii = 0; ii <= (i_secondCut - i_firstCut) / 2; ii++)
	{
		std::swap(genotypeVector.at(i_firstCut + ii), genotypeVector.at(i_secondCut - ii));
	}
	*/
}



template <class T> double Individual<T>::getFittness()
{
	return fittness;
}

template <class T> double Individual<T>::getRandomProbability()
{	
	return realDistribution(randomGenerator);
}

template <class T> int Individual<T> ::getCuttingPoint()
{
	return intDistribution(randomGenerator);
}
