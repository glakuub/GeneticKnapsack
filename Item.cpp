#include "Item.h"



Item::Item(double dSize, double dValue, double dCanTakeNTimes) :size(dSize), value(dValue), canTakeNTimes(dCanTakeNTimes)
{

}


Item::~Item()
{
}
double Item::getSize()
{
	return size;
}
double Item::getValue()
{
	return value;
}
double Item::howManyCanGet()
{
	return canTakeNTimes;
}