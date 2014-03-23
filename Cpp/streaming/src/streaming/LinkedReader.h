#ifndef __CHAIN_READER_H
#define __CHAIN_READER_H


#include "Reader.h"
#include "Adaptor.h"



template<typename UT, typename T>
class LinkedReader: public BufferReader<T>
{
public:
	LinkedReader(BufferReader<UT>* ipUpstream, Adaptor<UT, T>* ipAdaptor)
		: mpUpstream(ipUpstream)
		, mpAdaptor(ipAdaptor)
	{}

	LinkedReader(const T* ipArray, size_t iSize)
		: mpUpstream(NULL)
		, mpAdaptor(NULL)
		, BufferReader(ipArray, iSize)
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

		size_t lCount = BufferReader<T>::Read(p, n);
		if(mpAdaptor)
		{
			while(lCount < n && mpAdaptor->operator()(mpUpstream, &(this->mBuffer), n - lCount) > 0)
			{
				lCount += BufferReader<T>::Read(p + lCount, n - lCount);
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
			while(this->mBuffer.Size() < n && mpAdaptor->operator()(mpUpstream, &(this->mBuffer), n - this->mBuffer.Size()))
			{
			}
		}
		return BufferReader<T>::Get(p, n);
	}

	~LinkedReader()
	{
		cout << "destructor of linked buffer\n";

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
	BufferReader<UT>* mpUpstream;
	Adaptor<UT, T>* mpAdaptor;
};

#endif
