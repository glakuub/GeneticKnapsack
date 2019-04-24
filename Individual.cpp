#include "Individual.h"



template <class T> Individual<T>::Individual(int iGenotypeSize, std::vector<Item> * pcItems, double dMutProb, double dCrossProb) : c_randomGenerator(c_randomDevice()), c_realDistribution(0,1), c_intDistribution(0, iGenotypeSize -1)
{	
	i_genotypeSize = iGenotypeSize;
	d_fittness = 0;
	v_itemsVector = pcItems;
	d_crossingProbability = dCrossProb;
	d_mutationProbalility = dMutProb;
}
template <class T> Individual<T> ::Individual(const Individual& cOther) :c_randomGenerator(c_randomDevice()), c_realDistribution(0, 1), c_intDistribution(0, cOther.i_genotypeSize - 1)
{	
	v_itemsVector = cOther.v_itemsVector;
	i_genotypeSize = cOther.i_genotypeSize;
	d_fittness = cOther.d_fittness;
	genotype = cOther.genotype;
	d_crossingProbability = cOther.d_crossingProbability;
	d_mutationProbalility = cOther.d_mutationProbalility;
	
}
template <class T> std::vector<T>& Individual<T>::vGetGenotype()
{
	return genotype;
}
template <class T> Individual<T>::~Individual()=default;

template <class T>  Individual<T> & Individual<T>::operator++ ()
{
	vMutate();
	return *this;
}
template <class T>  Individual<T> & Individual<T>::operator++ (int)
{
	vMutate();
	return *this;
}
template <class T>  Individual<T> Individual<T>::operator+ (const Individual<T> & cOther)
{
	Individual<T>  pc_child(i_genotypeSize,v_itemsVector,d_mutationProbalility,d_crossingProbability);

	int i_cuttingPoint = iGetCuttingPoint();
	for (int ii = 0; ii < i_cuttingPoint; ii++)
	{
		pc_child.vGetGenotype().push_back(genotype.at(ii));
		
	}
	for (int ii = i_cuttingPoint; ii < i_genotypeSize; ii++)
	{
		pc_child.vGetGenotype().push_back(cOther.genotype.at(ii));
	}
	
	return pc_child;
}
template <> void Individual<int>::vCreateGenotype(std::vector<Item>* pvItems)
{
	if (genotype.empty())
	{	
		

		for (int ii = 0; ii < i_genotypeSize; ii++)
		{	
			std::uniform_int_distribution<>c_intDistribution(0, pvItems->at(ii).dHowManyCanGet());
			int i_gene = c_intDistribution(c_randomGenerator);
			genotype.push_back(i_gene);
		}
	}
}
template <> void Individual<double>::vCreateGenotype(std::vector<Item>* pvItems)
{
	if (genotype.empty())
	{	
		

		for (int ii = 0; ii < i_genotypeSize; ii++)
		{	
			std::uniform_real_distribution<>c_realDistribution(0, pvItems->at(ii).dHowManyCanGet());
			double d_gene = c_realDistribution(c_randomGenerator);
			genotype.push_back(d_gene);
		}
	}
}
template<> void Individual<bool>::vCreateGenotype()
{
	if (genotype.empty())
	{	
		
		std::uniform_int_distribution<>c_intDistribution(0, 1);
		for (int ii = 0; ii < i_genotypeSize; ii++)
		{	
			bool b_gene = c_intDistribution(c_randomGenerator);
			genotype.push_back(b_gene);
		}
	}
}




template <class T> void Individual<T>::vShowGenotype()
{	

	if (!genotype.empty())
	{	
	
		std::cout << std::endl;
		for (int ii = 0; ii < i_genotypeSize; ii++)
		{
			std::cout << genotype.at(ii) <<SPACE;
		}
	}
	
}

template <class T> void Individual<T>::vCalculateFittness(KnapsackProblem<T> * pcProblem)
{	
	d_fittness = pcProblem->dCalculateFitness(genotype);
	
}



template <class T> void Individual<T>::vTryToMutate()
{
	if (dGetRandomProbability() < d_mutationProbalility)
	{
		(*this)++;
	}
}

template <> void Individual<bool>::vMutate()
{		

	for (int ii = 0; ii < genotype.size(); ii++)
	{
		if (dGetRandomProbability() < d_mutationProbalility)
		{
			genotype.at(ii) = !genotype.at(ii);
		}
	}
	/*
		int i_firstCut = iGetCuttingPoint();
		if (i_firstCut == 0)i_firstCut++;
		int i_secondCut = 0;
		do {
			i_secondCut = iGetCuttingPoint();
		} while (i_firstCut == i_secondCut || i_secondCut == 0);

		if (i_secondCut < i_firstCut)
		{
			int temp = i_secondCut;
			i_secondCut = i_firstCut;
			i_firstCut = temp;
		}
		for (int ii = 0; ii <= (i_secondCut - i_firstCut) / 2; ii++)
		{
			std::swap(genotype.at(i_firstCut+ii), genotype.at(i_secondCut - ii));
		}
		*/
}
template <> void Individual<int>::vMutate()
{
	for (int ii = 0; ii < genotype.size(); ii++)
	{	
		if (dGetRandomProbability() < d_mutationProbalility)
		{	
			if (dGetRandomProbability() < d_mutationProbalility)
			{
				int d_howMany = v_itemsVector->at(ii).dHowManyCanGet();
				int d_mutationRange = d_howMany / 2;

				std::uniform_int_distribution<> c_mutationValue(-d_mutationRange, d_mutationRange);
				genotype.at(ii) = genotype.at(ii) + c_mutationValue(c_randomGenerator);
				if (genotype.at(ii) > d_howMany)
				{
					genotype.at(ii) = d_howMany;
				}
				if (genotype.at(ii) < 0)
				{
					genotype.at(ii) = 0;
				}

			}
			genotype.at(ii) = v_itemsVector->at(ii).dHowManyCanGet() - genotype.at(ii);
		}
	}
	/*
	int i_firstCut = iGetCuttingPoint();
	if (i_firstCut == 0)i_firstCut++;
	int i_secondCut = 0;
	do {
		i_secondCut = iGetCuttingPoint();
	} while (i_firstCut == i_secondCut || i_secondCut == 0);

	if (i_secondCut < i_firstCut)
	{
		int temp = i_secondCut;
		i_secondCut = i_firstCut;
		i_firstCut = temp;
	}
	for (int ii = 0; ii <= (i_secondCut - i_firstCut) / 2; ii++)
	{
		std::swap(genotype.at(i_firstCut + ii), genotype.at(i_secondCut - ii));
	}
	*/
}
template <> void Individual<double>::vMutate()
{
	for (int ii = 0; ii < genotype.size(); ii++)
	{
		if (dGetRandomProbability() < d_mutationProbalility)
		{	
			double d_howMany = v_itemsVector->at(ii).dHowManyCanGet();
			double d_mutationRange = d_howMany/10.0;

			std::uniform_real_distribution<> c_mutationValue(-d_mutationRange, d_mutationRange);
			genotype.at(ii) = genotype.at(ii) + c_mutationValue(c_randomGenerator);
			if (genotype.at(ii) > d_howMany)
			{
				genotype.at(ii) = d_howMany;
			}
			if (genotype.at(ii) < 0)
			{
				genotype.at(ii) = 0;
			}
			
			
		}
	}
	/*
	int i_firstCut = iGetCuttingPoint();
	if (i_firstCut == 0)i_firstCut++;
	int i_secondCut = 0;
	do {
		i_secondCut = iGetCuttingPoint();
	} while (i_firstCut == i_secondCut || i_secondCut == 0);

	if (i_secondCut < i_firstCut)
	{
		int temp = i_secondCut;
		i_secondCut = i_firstCut;
		i_firstCut = temp;
	}
	for (int ii = 0; ii <= (i_secondCut - i_firstCut) / 2; ii++)
	{
		std::swap(genotype.at(i_firstCut + ii), genotype.at(i_secondCut - ii));
	}
	*/
}



template <class T> double Individual<T>::dGetFittness()
{
	return d_fittness;
}

template <class T> double Individual<T>::dGetRandomProbability()
{	
	return c_realDistribution(c_randomGenerator);
}

template <class T> int Individual<T> ::iGetCuttingPoint()
{
	return c_intDistribution(c_randomGenerator);
}
