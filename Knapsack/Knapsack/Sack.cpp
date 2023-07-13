#include "Sack.h"

Sack::Sack(int w)
{
	weight = 0;
	maxWeight = w;
	value = 0;
	numItems = 0;
	inSack = new Object[0];
}

void Sack::addItem(Object* newItem)
{
	if (weight + newItem->getWeight() <= maxWeight)
	{
		numItems++;
		Object* temp = new Object[numItems];
		for (int i = 0; i < numItems-1; i++)
			temp[i] = inSack[i];
		temp[numItems - 1] = *newItem;
		value += newItem->getValue();
		weight += newItem->getWeight();
		inSack = temp;
	}
}

void Sack::removeLast()
{
	if (numItems > 0)
	{
		numItems--;
		Object* temp = new Object[numItems];
		for (int i = 0; i < numItems - 1; i++)
			temp[i] = inSack[i];
		inSack = temp;
	}
}

int Sack::getNumItems()
{
	return numItems;
}

int Sack::getValue()
{
	return value;
}

void Sack::sortSack()
{
	for (int i = 0; i < numItems; i++)
	{
		for (int j = 0; j < numItems - i; j++)
		{
			Object o1 = inSack[j];
			Object o2 = inSack[j + 1];
			if (o1.getValue() < o2.getValue())
			{
				inSack[j] = o2;
				inSack[j + 1] = o1;
			}
		}
	}
	return;
}

void Sack::weightedSort()
{
	for (int i = 0; i < numItems; i++)
	{
		for (int j = 0; j < numItems - i; j++)
		{
			Object o1 = inSack[j];
			Object o2 = inSack[j + 1];
			if ((1.0 * o1.getValue()) / o1.getWeight() < (1.0 * o2.getValue()) / o2.getWeight())
			{
				inSack[j] = o2;
				inSack[j + 1] = o1;
			}
		}
	}
	return;
}

int Sack::getMaxWeight()
{
	return maxWeight;
}

int Sack::getWeight()
{
	return weight;
}

Object* Sack::getItem(int i)
{
	return &inSack[i];
}