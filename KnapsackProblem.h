#pragma once
#include <vector>
#include "Item.h"
template <class T>
class KnapsackProblem
{
public:
	KnapsackProblem();
	~KnapsackProblem();
	int iSetProperties( double dKnapsackSize, int iItemsNumber, std::vector<Item>* pvItemsVector);
	double dGetKnapsackSize();
	double dCalculateFitness(std::vector<T> & vGenotype);
	int iGetItemsNumber();
	std::vector<Item>* pvGetItems();
	
	
private:
	
	int i_itemsNumber;
	double d_knapsackSize;
	std::vector<Item>* pv_items;
	static const int ERR_LESS_THAN_ONE_ITEM = -7;
	static const int ERR_KNAPSACK_SIZE_ZERO_OR_LESS = -8;
	static const int ERR_INCORRECT_ITEMS_VECTOR = -9;
};

template class KnapsackProblem<bool>;
template class KnapsackProblem<int>;
template class KnapsackProblem<double>;