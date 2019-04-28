#pragma once
#include <Windows.h>


template<typename T>
class DynamicArray
{
public:
	DynamicArray(int nInitialSize = 0)
	{
		int nSize = nInitialSize;
		if (nSize < 1)
			nSize = 1;

		m_pData = new T[nSize];
		m_nTotalSize = nSize;
		m_nUsedCount = 0;
	}

	//Copy constructor
	DynamicArray(DynamicArray& array)
	{
		m_nTotalSize = array.m_nTotalSize;
		m_pData = new T[m_nTotalSize];
		m_nUsedCount = array.m_nUsedCount;
		for (int i = 0; i < m_nUsedCount; ++i)
		{
			m_pData[i] = array.m_pData[i];
		}
	}

	~DynamicArray()
	{
		delete[] m_pData;
	}

	//Add a new value to the start of the list
	void PushFront(T data)
	{
		++m_nUsedCount;
		Resize();

		for (int i = m_nUsedCount - 1; i >= 0; --i)
		{
			m_pData[i + 1] = m_pData[i];
		}
		m_pData[0] = data;
	}

	//Add a new value to the end of the list
	void PushBack(T data)
	{
		//Check for space
		Resize();

		m_pData[m_nUsedCount] = data;
		++m_nUsedCount;
	}

	//Add a new value one past the specified index location
	void Insert(int nIndex, T data)
	{
		++m_nUsedCount;
		Resize();

		for (int i = m_nUsedCount - 1; i >= nIndex; --i)
		{
			m_pData[i + 1] = m_pData[i];
		}
		m_pData[nIndex] = data;
	}

	//Return the first element 
	T First()
	{
		return m_pData[0];
	}

	//Return the last element
	T Last()
	{
		return m_pData[m_nUsedCount - 1];
	}

	//Return how many elements exist in the list
	int Count()
	{
		return m_nUsedCount;
	}

	//Remove an element by its index
	void Erase(int nIndex)
	{
		for (int i = nIndex; i < m_nUsedCount; ++i)
		{
			m_pData[i] = m_pData[i + 1];
		}
		--m_nUsedCount;
	}

	//Remove all elements with the matching value
	void Remove(int nValue)
	{
		int nCurrentCount = m_nUsedCount;
		for (int i = 0; i < nCurrentCount; ++i)
		{
			if (m_pData[i] == nValue)
			{
				Erase(i);
				--i;
			}
		}
	}

	//Remove the last element
	void PopBack()
	{
		--m_nUsedCount;
	}

	//Remove the first element
	void PopFront()
	{
		for (int i = 0; i < m_nUsedCount; ++i)
		{
			m_pData[i] = m_pData[i + 1];
		}
		--m_nUsedCount;
	}

	//Return a bool, true if empty, false otherwise
	bool Empty()
	{
		if (m_nUsedCount <= 0)
			return true;
		else
			return false;
	}

	//Remove all elements from the list
	void Clear()
	{
		int nDeleteCount = m_nUsedCount;
		for (int i = 0; i < nDeleteCount; ++i)
		{
			--m_nUsedCount;
		}
	}

	//Print the whole array
	void Print()
	{
		for (int i = 0; i < m_nUsedCount; ++i)
		{
			std::cout << m_pData[i] << std::endl;
		}
	}

	
	int GetSize()
	{
		return m_nUsedCount;
	}

	//Lets us use square brackets when using the array
	T& operator[](int nIndex)
	{
		return m_pData[nIndex];
	}

	//Returns the value at the index so that pointers to a dynamic array can be used
	T Return(int nIndex)
	{
		return m_pData[nIndex];
	}

private:
	void Resize()
	{
		//Run out of space
		if (m_nUsedCount >= m_nTotalSize)
		{
			T* pBiggerArray = new T[m_nTotalSize * 2];
					//New array,	new array size,				source array	source array size
			memcpy_s(pBiggerArray, sizeof(T) * m_nTotalSize * 2, m_pData, sizeof(T) * m_nTotalSize);
			delete[] m_pData;

			//Update the pointer
			m_pData = pBiggerArray;

			m_nTotalSize *= 2;
		}
	}

	//Actual array
	T* m_pData;

	int m_nTotalSize;
	int m_nUsedCount;
};