#include "KnapsackProblem.h"


template <class T>
KnapsackProblem<T>::KnapsackProblem()
{	
	pv_items = nullptr;
	d_knapsackSize = 0;
	i_itemsNumber = 0;
}

template <class T> KnapsackProblem<T>::~KnapsackProblem()=default;


template <class T>
int KnapsackProblem<T>::iSetProperties(double dKnapsackSize, int iItemsNumber, std::vector<Item>* pvItems)
{
	{

		if (iItemsNumber < 1) return ERR_LESS_THAN_ONE_ITEM;
		i_itemsNumber = iItemsNumber;
		if (dKnapsackSize <= 0) return ERR_KNAPSACK_SIZE_ZERO_OR_LESS;
		d_knapsackSize = dKnapsackSize;
		if (pvItems->size() != iItemsNumber)return ERR_INCORRECT_ITEMS_VECTOR;
		pv_items = pvItems;

		return 1;

	}
}


template <class T> double KnapsackProblem<T>::dCalculateFitness(std::vector<T> & vGenotype)
{
	double d_value = 0;
	double d_usedSpace = 0;

	for (int ii = 0; ii < i_itemsNumber; ii++)
	{

		d_value += vGenotype.at(ii) * (pv_items->at(ii)).getValue();
		d_usedSpace += vGenotype.at(ii) * (pv_items->at(ii)).getSize();

	}
	if (d_usedSpace > d_knapsackSize)
	{
		d_value = 0;
	}
	return d_value;
}
template <class T> double KnapsackProblem<T>::dGetKnapsackSize()
{
	return d_knapsackSize;
}
template <class T> int KnapsackProblem<T>::iGetItemsNumber()
{
	return i_itemsNumber;
}

template <class T> std::vector<Item>* KnapsackProblem<T>::pvGetItems()
{
	return pv_items;
}
