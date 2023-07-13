#include "iostream"
#include <stdlib.h>
#include "Sack.h"
#include <fstream>

void addItem(Sack* allItems);
void iterateFile(Sack* allItems);
void valueOnly(Sack* allItems, int w);
void valueWeighted(Sack* allItems, int w);
void printSack(Sack* allItems);
Sack* greedySelection(Sack* allItems, int w);
Sack* moreValue(Sack* first, Sack* second);
Sack* dynamicSelection(Sack* all, Sack* toUse, int index, int weight);

int main()
{
	Sack* allItems = new Sack(INT_MAX);
	std::cout << "Welcome to the sack! " << std::endl;
	int option = 0;
	while (option != 5)
	{
		std::cout << "Enter option of what to do" << std::endl <<
			"1) Add to the sack.\n2) Remove last item.\n3) See the sack.\n4) Read from file.\n5) Stop.\nOption = ";
		std::cin >> option;
		if (option == 1) {
			addItem(allItems);
		}
		else if (option == 2)
		{
			allItems->removeLast();
		}
		else if (option == 3)
		{
			for (int i = 0; i < allItems->getNumItems(); i++)
			{
				std::cout << "Item " << i << " (Value = " << allItems->inSack[i].getValue() << ", Weight = " << allItems->inSack[i].getWeight() << ")" << std::endl;
			}
		}
		
		else if (option == 4)
		{
			iterateFile(allItems);
		}
		else if (option != 5)
		{
			std::cout << "Not a valid option!" << std::endl;
		}
		system("PAUSE");
		system("CLS");
	}
	//Origina Sack
	std::cout << "Original Sack" << std::endl;
	printSack(allItems);
	//Max Weight for sack
	int mW;
	std::cout << "Enter max weight of sack: ";
	std::cin >> mW;
	//Dynamic Sort
	Sack* dynoSack = dynamicSelection(allItems, new Sack(mW), 0, mW);
	
	std::cout << "Dynamic Programming\n" << "Total Value = " << dynoSack->getValue() << std::endl;
	printSack(dynoSack);
	//Greedy Sort
	valueOnly(allItems, mW);
	//Weighted Greedy Sort
	valueWeighted(allItems, mW);
}

void addItem(Sack* allItems)
{
	int weight;
	int value;
	std::cout << "Enter the item value: ";
	std::cin >> value;
	std::cout << "Enter the item weight: ";
	std::cin >> weight;
	Object* newObj = new Object(value, weight);
	allItems->addItem(newObj);
}

void iterateFile(Sack* allItems)
{
	std::ifstream indata;
	indata.open("values.txt");
	if (!indata)
	{
		std::cout << "Could not find file" << std::endl;
		return;
	}
	int weight, value;
	indata >> weight >> value;
	while (!indata.eof())
	{
		Object* newObj = new Object(value, weight);
		allItems->addItem(newObj);
		indata >> weight >> value;
	}
	indata.close();
	std::cout << "End of file reached" << std::endl;
	return;
}

Sack* greedySelection(Sack* allItems, int w)
{
	int total = 0;
	Sack* finalSack = new Sack(w);
	for (int i = 0; i < allItems->getNumItems(); i++)
	{
		if (finalSack->getWeight() + allItems->inSack[i].getWeight() <= finalSack->getMaxWeight())
		{
			//fixing here
			finalSack->addItem(&allItems->inSack[i]);
			total += allItems->inSack[i].getValue();
		}
	}
	std::cout << "Total Value = " << total << std::endl;
	return finalSack;
}

Sack* moreValue(Sack* first, Sack* second)
{
	if (first->getValue() >= second->getValue())
		return first;
	else
		return second;
}

void valueOnly(Sack* allItems, int w)
{
	std::cout << "Sorted Sack\n";
	allItems->sortSack();
	Sack* finalSack = greedySelection(allItems, w);
	printSack(finalSack);
}

void valueWeighted(Sack* allItems, int w)
{
	std::cout << "Weighted Sack\n";
	allItems->weightedSort();
	Sack* finalSack2 = greedySelection(allItems, w);
	printSack(finalSack2);
}

void printSack(Sack* allItems)
{
	for (int i = 0; i < allItems->getNumItems(); i++)
	{
		std::cout << "Item " << i << " (Value = " << allItems->inSack[i].getValue() << ", Weight = " << allItems->inSack[i].getWeight() << ")" << std::endl;
	}
	system("PAUSE");
}

Sack* dynamicSelection(Sack* all, Sack* toUse, int index, int weight)
{
	//check if you are at the end of the array
	if (index >= all->getNumItems())
	{
		return toUse;
	}
	//check if you  can add the item to the sack
	else if (all->inSack[index].getWeight() + toUse->getWeight() <= weight)
	{
		Sack* with = new Sack(weight);
		Sack* out = new Sack(weight);
		for (int i = 0; i < toUse->getNumItems(); i++)
		{
			with->addItem(&toUse->inSack[i]);
			out->addItem(&toUse->inSack[i]);
		}
		with->addItem(&all->inSack[index]);
		return moreValue(dynamicSelection(all, out, index + 1, weight), dynamicSelection(all, with, index + 1, weight));
	}
	//if can't, just try without
	else
	{
		Sack* out = new Sack(weight);
		for (int i = 0; i < toUse->getNumItems(); i++)
		{
			out->addItem(&toUse->inSack[i]);
		}
		return dynamicSelection(all, out, index + 1, weight);
	}
}