#pragma once
#include <vector>
#include "Item.h"
template <class T>
class KnapsackProblem
{
public:
	KnapsackProblem();
	~KnapsackProblem();
	int setParameters(double dKnapsackSize, int iItemsNumber, std::vector<Item> *pvItemsVector);
	double getKnapsackSize();
	double calculateFitness(std::vector<T> &vGenotype);
	int getItemsNumber();
	std::vector<Item>* getItemsVector();
	
	
private:
	
	int itemsNumber;
	double knapsackSize;
	std::vector<Item>* pv_items;
	static const int ERR_LESS_THAN_ONE_ITEM = -7;
	static const int ERR_KNAPSACK_SIZE_ZERO_OR_LESS = -8;
	static const int ERR_INCORRECT_ITEMS_VECTOR = -9;
};

template class KnapsackProblem<bool>;
template class KnapsackProblem<int>;
template class KnapsackProblem<double>;