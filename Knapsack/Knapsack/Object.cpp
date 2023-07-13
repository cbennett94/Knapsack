#include "Object.h"

Object::Object()
{
	value = 0;
	weight = 0;
}

Object::Object(int v, int w)
{
	value = v;
	weight = w;
}

int Object::getValue()
{
	return value;
}

int Object::getWeight()
{
	return weight;
}