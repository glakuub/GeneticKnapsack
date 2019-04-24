#pragma once
#include <vector>
#include "CItem.h"
template <class T>
class CKnapsackProblem
{
public:
	CKnapsackProblem();
	~CKnapsackProblem();
	int iSetProperties( double dKnapsackSize, int iItemsNumber, std::vector<CItem>* pvItemsVector);
	double dGetKnapsackSize();
	double dCalculateFitness(std::vector<T> & vGenotype);
	int iGetItemsNumber();
	std::vector<CItem>* pvGetItems();
	
	
private:
	
	int i_itemsNumber;
	double d_knapsackSize;
	std::vector<CItem>* pv_items;
	static const int ERR_LESS_THAN_ONE_ITEM = -7;
	static const int ERR_KNAPSACK_SIZE_ZERO_OR_LESS = -8;
	static const int ERR_INCORRECT_ITEMS_VECTOR = -9;
};

template class CKnapsackProblem<bool>;
template class CKnapsackProblem<int>;
template class CKnapsackProblem<double>;