#pragma once
#include <iostream>
#include "DynamicArray.h"

class Sequence
{
public:
	Sequence();
	~Sequence();

	//Produces a number from 1-4 and adds it to the sequence
	void AddDirection();

	//Returns true if the input was the same direction as the direction in the sequence
	bool CheckDirection(int nSequenceIndex, int nDirectionIndex);


private:


	//The array
	DynamicArray<int>* m_pSequence;

};