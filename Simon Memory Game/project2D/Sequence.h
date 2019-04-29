#pragma once
#include <iostream>
#include "DynamicArray.h"

enum Directions
	{
		RIGHT	= 1,
		LEFT	= 2,
		DOWN	= 3,
		UP		= 4,
	};

class Sequence
{
public:
	Sequence();
	~Sequence();


	//Produces a number from 1-4 and adds it to the sequence
	void AddDirection();

	//Returns true if the input was the same direction as the direction in the sequence
	bool CheckDirection(int nSequenceIndex, int nDirectionIndex);

	//Returns how many directions are currently in the sequence
	int SequenceCount();

	//Deletes all directions from the sequence
	void SequenceClear();

	//Operator overloader so square brackets can be used for indexes
	int& operator[](int nIndex);


private:

	//The array
	DynamicArray<int>* m_pSequence;
};