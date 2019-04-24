#include <iostream>
#include "KnapsackProblem.h"


template <class T>
KnapsackProblem<T>::KnapsackProblem()
{	
	pv_items = nullptr;
	knapsackSize = 0;
	itemsNumber = 0;
}

template <class T> KnapsackProblem<T>::~KnapsackProblem()=default;


template <class T>
int KnapsackProblem<T>::setParameters(double dKnapsackSize, int iItemsNumber, std::vector<Item> *pvItems)
{
	{

		if (iItemsNumber < 1) return ERR_LESS_THAN_ONE_ITEM;
		itemsNumber = iItemsNumber;
		if (dKnapsackSize <= 0) return ERR_KNAPSACK_SIZE_ZERO_OR_LESS;
		knapsackSize = dKnapsackSize;
		if (pvItems->size() != iItemsNumber)return ERR_INCORRECT_ITEMS_VECTOR;
		pv_items = pvItems;

		return 1;

	}
}


template <class T> double KnapsackProblem<T>::calculateFitness(std::vector<T> &vGenotype)
{
	double d_value = 0;
	double d_usedSpace = 0;

	for (int ii = 0; ii < itemsNumber; ii++)
	{

		d_value += vGenotype.at(ii) * (pv_items->at(ii)).getValue();
		d_usedSpace += vGenotype.at(ii) * (pv_items->at(ii)).getSize();

	}
	std::cout<<d_usedSpace<<"<-->"<<knapsackSize<<std::endl;
	if (d_usedSpace > knapsackSize)
	{
		d_value = 0;
	}
	return d_value;
}
template <class T> double KnapsackProblem<T>::getKnapsackSize()
{
	return knapsackSize;
}
template <class T> int KnapsackProblem<T>::getItemsNumber()
{
	return itemsNumber;
}

template <class T> std::vector<Item>* KnapsackProblem<T>::getItemsVector()
{
	return pv_items;
}
