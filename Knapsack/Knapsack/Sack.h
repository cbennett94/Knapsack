#pragma once
#include "Object.h"
class Sack
{
protected:
	int weight;
	int maxWeight;
	int value;
	int numItems;

public:
	Object* inSack;
	Sack(int w);
	void addItem(Object* newItem);
	void removeLast();
	int getValue();
	int getNumItems();
	void sortSack();
	void weightedSort();
	int getWeight();
	int getMaxWeight();
	Object* getItem(int i);
};