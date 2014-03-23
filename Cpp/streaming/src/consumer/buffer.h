#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <iostream>

#include "consumer.h"

template<typename T>
class Buffer
{
public:
	Buffer(size_t iCapacity)
		: mpData(NULL)
		, mpCurrent(NULL)
		, mpEnd(NULL)
		, mpDataEnd(NULL)
		, mVersion(0)
	{
		// allocate buffer
		mpData = new T[iCapacity];

		// set status
		mpCurrent = mpEnd = mpData;
		mpDataEnd = mpData + iCapacity;

		std::cout << "Write buffer constructor\n";
	}

	Buffer(const T* ipArray = NULL, size_t n = 0)
		: mpData(NULL)
		, mpCurrent(NULL)
		, mpEnd(NULL)
		, mpDataEnd(NULL)
		, mVersion(0)
	{
		// allocate buffer
		size_t lCapacity = 10 < n ? n: 10;
		mpData = new T[lCapacity];

		// set status
		mpCurrent = mpEnd = mpData;
		mpDataEnd = mpData + lCapacity;

		// copy content
		if(n > 0 && ipArray != NULL)
		{
			mpEnd = mpData + n;
			for(T *lpDest = mpData; lpDest < mpEnd;)
			{
				*(lpDest++) = *(ipArray++);
			}
		}

		std::cout << "Read buffer constructor\n";
	}

	size_t More(size_t n)
	{
		return 0;
	}

	Consumer<T>* GetReader()
	{
		return new Consumer<T>(&mpData, &mpCurrent, &mpEnd);
	}

	Consumer<T>* GetWriter()
	{
		return new Consumer<T>(&mpCurrent, &mpEnd, &mpDataEnd);
	}

	~Buffer()
	{
		delete [] mpData;
	}

private:
	T* mpData;
	T* mpCurrent;
	T* mpEnd;
	T* mpDataEnd;
	size_t mVersion;
};

#endif