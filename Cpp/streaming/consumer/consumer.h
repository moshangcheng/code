#ifndef __CONSUMER_H__
#define __CONSUMER_H__

#include <iostream>

/*
	read and write are dual operations
	read is operation of occupied space
	write is operation of not occupied space
	see implementation of streambuf in VC2010
	std::basic_stringbuf is a good choic if std:move in C++11 used
*/

template<typename T>
class Consumer
{
public:
	Consumer(T** ippData, T** ippCurrent, T** ippEnd)
		: mppData(ippData)
		, mppCurrent(ippCurrent)
		, mppEnd(ippEnd)
	{}

	const T* Current() const
	{
		return *mppCurrent;
	}

	const T* End() const
	{
		return *mppEnd;
	}

	size_t Size() const
	{
		return (*mppEnd) - (*mppCurrent);
	}

	size_t Get(T** p, size_t n = 1)
	{
		if(n == 0)
		{
			*p = NULL;
			return 0;
		}

		*p = *mppCurrent;
		size_t lCount = n < Size() ? n: Size();
		*mppCurrent += lCount;
		return lCount;
	}

	// Go backward
	bool UnGet(size_t n = 1)
	{
		if(n > Size())
		{
			return false;
		}
		*mppCurrent -= n;
		return true;
	}

private:
	T** mppData;
	T** mppCurrent;
	T** mppEnd;
};

#endif