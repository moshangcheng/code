#ifndef __READER_H
#define __READER_H

#include "Buffer.h"


template<typename T>
class Reader
{
public:

	Reader()
	{
		std::cout << "Reader constructor\n";
	}

	// read with copy, caller are responsible to allocate memory
	virtual size_t Read(T* p, size_t n = 1)
	{
		return 0;
	}

	virtual ~Reader() throw()
	{
		std::cout << "Reader destructor\n";
	}
};


template<typename T>
class BufferReader: public Reader<T>
{
public:
	BufferReader(const T* ipArray = NULL, size_t n = 0)
		: mBuffer(ipArray, n)
	{}


	virtual size_t Read(T* p, size_t n = 1)
	{
		T* lpBegin = NULL;
		size_t lCount = mBuffer.Get(&lpBegin, n);

		for(const T* lpEnd = lpBegin + lCount; lpBegin < lpEnd;)
		{
			*(p++) = *(lpBegin++);
		}

		return lCount;
	}

	virtual size_t Get(T** p, size_t n = 1)
	{
		return mBuffer.Get(p, n);
	}

	virtual bool UnGet(size_t n = 1)
	{
		return mBuffer.UnGet(n);
	}

	virtual ~BufferReader() throw()
	{
	}

protected:
	Buffer<T> mBuffer;
};

#endif
