#ifndef __LINKED_READER_H
#define __LINKED_READER_H


#include "Buffer.h"
#include "Adaptor.h"



template<typename UT, typename T>
class LinkedReader: public Buffer<T>
{
public:
	LinkedReader(Buffer<UT>* ipUpstream, Adaptor<UT, T>* ipAdaptor)
		: mpUpstream(ipUpstream)
		, mpAdaptor(ipAdaptor)
	{}

	LinkedReader(const T* ipArray, size_t iSize)
		: mpUpstream(NULL)
		, mpAdaptor(NULL)
		, Buffer(ipArray, iSize)
	{}

	template<typename DT>
	LinkedReader<T, DT>* Pipe(Adaptor<T, DT>* ipAdaptor)
	{
		return new LinkedReader<T, DT>(this, ipAdaptor);
	}

	//read with copy, caller are responsible to allocate memory
	virtual size_t Read(T* p, size_t n = 1)
	{
		if(n == 0)
		{
			return 0;
		}

		size_t lCount = Buffer<T>::Read(p, n);
		if(mpAdaptor)
		{
			while(lCount < n && (*mpAdaptor)(mpUpstream, this, 0, n - lCount) > 0)
			{
				lCount += Buffer<T>::Read(p + lCount, n - lCount);
			}
		}
		return lCount;
	}

	virtual size_t Get(T** p, size_t n = 1)
	{
		if(n == 0)
		{
			return 0;
		}

		if(mpAdaptor)
		{
			while(this->Size() < n && (*mpAdaptor)(mpUpstream, this, 0, n - this->Size()))
			{
			}
		}
		return Buffer<T>::Get(p, n);
	}

	~LinkedReader()
	{
		cout << "destructor of linked buffer reader \n";

		if(mpUpstream)
		{
			delete mpUpstream;
			mpUpstream = NULL;
		}

		if(mpAdaptor)
		{
			delete mpAdaptor;
			mpAdaptor = NULL;
		}
	}

private:
	Buffer<UT>* mpUpstream;
	Adaptor<UT, T>* mpAdaptor;
};


class ReaderFactory
{
public:
	template<typename T>
	static LinkedReader<T, T>* FromArray(const T* ipArray, size_t n)
	{
		return new LinkedReader<T, T>(ipArray, n);
	}

	template<typename UT, typename T>
	static LinkedReader<UT, T>* FromAdaptor(Adaptor<UT, T>* ipAdaptor)
	{
		return new LinkedReader<UT, T>(NULL, ipAdaptor)
	}
};

#endif
