#pragma once
class Object {
protected: 
	int value;
	int weight;
public:
	Object();
	Object(int v, int w);
	int getWeight();
	int getValue();
};