#include "Sequence.h"

Sequence::Sequence()
{
	//Start the sequence array with 25 empty spots
	m_pSequence = new DynamicArray<int>(25);
	AddDirection();
}

Sequence::~Sequence()
{

}


void Sequence::AddDirection()
{
	//						1-4
	m_pSequence->PushBack((rand() % (4)) + 1);
}

bool Sequence::CheckDirection(int nSequenceIndex, int nDirectionIndex)
{
	return (m_pSequence[nSequenceIndex] == nDirectionIndex);
}

//Trying to get the pointer to the dynamic array to work. Need it to return the value at the index
//Need to at a direction to index converter / enums