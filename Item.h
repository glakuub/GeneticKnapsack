#pragma once
class Item
{
public:
	Item(double dSize,double dValue,double dCanTakeNTimes);
	~Item();
	double getSize();
	double getValue();
	double howManyCanGet();
private:
	double size;
	double value;
	double canTakeNTimes;
};

