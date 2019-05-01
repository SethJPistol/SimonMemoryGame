#include "Sequence.h"

Sequence::Sequence()
{
	//Start the sequence array with 25 empty spots
	m_pSequence = new DynamicArray<int>(25);
	AddDirection();
}

Sequence::~Sequence()
{
	delete m_pSequence;
	m_pSequence = nullptr;
}


void Sequence::AddDirection()
{
	assert(m_pSequence);
	//						1-4
	m_pSequence->PushBack((rand() % (4)) + 1);
}

bool Sequence::CheckDirection(int nSequenceIndex, int nDirectionIndex)
{
	assert(m_pSequence);
	//Make sure the number in the sequence is actually a direction
	assert((*m_pSequence)[nSequenceIndex] >= 1 && (*m_pSequence)[nSequenceIndex] <= 4);
	return ((*m_pSequence)[nSequenceIndex] == nDirectionIndex);
}

int Sequence::SequenceCount()
{
	assert(m_pSequence);
	return m_pSequence->Count();
}

void Sequence::SequenceClear()
{
	assert(m_pSequence);
	m_pSequence->Clear();
}

int& Sequence::operator[](int nIndex)
{
	assert(m_pSequence);
	return (*m_pSequence)[nIndex];
}