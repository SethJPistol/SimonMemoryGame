#pragma once
#include <Windows.h>
#include <assert.h>


template<typename T>
class DynamicArray
{
public:

	//List of all public functions:

	//---------------------------------------------------------------------------------------
	/*DynamicArray(int nInitialSize);	Constructor
	~DynamicArray();					Destructor
	DynamicArray(DynamicArray& array);	Copy constructor

	void Insert(int nIndex, T data);	Add a new value one past the specified index location
	void PushFront(T data);				Add a new value to the start of the list
	void PushBack(T data);				Add a new value to the end of the list
	T First();							Return the first element
	T Last();							Return the last element
	int Count();						Return how many elements exist in the list
	void Erase(int nIndex);				Remove an element by its index
	void Remove(int nValue);			Remove all elements with the matching value
	void Clear();						Remove all elements from the list
	void PopBack();						Remove the last element
	void PopFront();					Remove the first element
	bool Empty();						Return a bool, true if empty, false otherwise
	void Print();						Print the whole array
	int GetSize();						Return how many elements in the array
	T& operator[](int nIndex);			Lets us use square brackets when using the array*/
	//---------------------------------------------------------------------------------------


	DynamicArray(int nInitialSize = 0)
	{
		int nSize = nInitialSize;
		if (nSize < 1)
			nSize = 1;

		m_pData = new T[nSize];
		m_nTotalSize = nSize;
		m_nUsedCount = 0;
	}

	~DynamicArray()
	{
		delete[] m_pData;
	}

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



	void Insert(int nIndex, T data)
	{
		assert(m_pData);
		++m_nUsedCount;
		//Check if a resize is needed
		Resize();

		//Shift any data after the insert point to the right by 1
		for (int i = m_nUsedCount - 1; i >= nIndex; --i)
		{
			m_pData[i + 1] = m_pData[i];
		}

		m_pData[nIndex] = data;
	}

	void PushFront(T data)
	{
		assert(m_pData);
		Insert(0, data);
	}

	void PushBack(T data)
	{
		assert(m_pData);
		//Check if a resize is needed
		Resize();

		m_pData[m_nUsedCount] = data;
		++m_nUsedCount;
	}

	T First()
	{
		assert(m_pData);
		return m_pData[0];
	}

	T Last()
	{
		assert(m_pData);
		return m_pData[m_nUsedCount - 1];
	}

	int Count()
	{
		assert(m_pData);
		return m_nUsedCount;
	}

	void Erase(int nIndex)
	{
		assert(m_pData);
		//Shift any data after the erase point to the left by 1
		for (int i = nIndex; i < m_nUsedCount; ++i)
		{
			m_pData[i] = m_pData[i + 1];
		}
		--m_nUsedCount;
	}

	void Remove(int nValue)
	{
		assert(m_pData);
		//Search for the value in the array
		for (int i = 0; i < m_nUsedCount; ++i)
		{
			if (m_pData[i] == nValue)
			{
				Erase(i);
				--i;
			}
		}
	}

	void Clear()
	{
		assert(m_pData);
		//Repeats until used count is 0
		while (m_nUsedCount)
		{
			--m_nUsedCount;
		}
	}

	void PopBack()
	{
		assert(m_pData);
		--m_nUsedCount;
	}

	void PopFront()
	{
		assert(m_pData);
		//Shift any data after the erase point to the left by 1
		for (int i = 0; i < m_nUsedCount; ++i)
		{
			m_pData[i] = m_pData[i + 1];
		}
		--m_nUsedCount;
	}

	bool Empty()
	{
		assert(m_pData);
		return m_nUsedCount <= 0;
	}

	void Print()
	{
		assert(m_pData);
		for (int i = 0; i < m_nUsedCount; ++i)
		{
			std::cout << m_pData[i] << std::endl;
		}
	}

	int GetSize()
	{
		assert(m_pData);
		return m_nUsedCount;
	}

	T& operator[](int nIndex)
	{
		assert(m_pData);
		return m_pData[nIndex];
	}

	//-------------------------------------------------------------------------------------------

private:

	void Resize()
	{
		assert(m_pData);
		//If out of space
		if (m_nUsedCount >= m_nTotalSize)
		{
			T* pBiggerArray = new T[m_nTotalSize * 2];
			//New array,    new array size,			  source array	source array size
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