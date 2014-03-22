#ifndef __CHAIN_READER_H
#define __CHAIN_READER_H


#include "Reader.h"
#include "Adaptor.h"

template<typename UT, typename T>
class ChainReader: public BufferReader<T>
{
public:
	ChainReader(BufferReader<UT>* ipUpstream, Adaptor<UT, T>* ipAdaptor)
		: mpAdaptor(ipAdaptor)
		, mpUpStream(ipUpstream)
	{
	}

	template<typename DT>
	ChainReader<T, DT>* Pipe(Adaptor<T, DT>* ipAdaptor)
	{
		return new ChainReader<T, DT>(this, ipAdaptor);
	}

	//read with copy, caller are responsible to allocate memory
	virtual size_t Read(T* p, size_t n = 1)
	{
		if(n == 0)
		{
			return 0;
		}

		size_t lCount = BufferReader<T>::Read(p, n);
		if(!mpAdaptor.IsNull())
		{
			while(lCount < n && mpAdaptor->operator()(mpUpStream.Get(), &(this->mBuffer)) > 0)
			{
				lCount += BufferReader<T>::Read(p + lCount, n - lCount);
			}
		}
		return lCount;
	}

	virtual size_t Get(const T** p, size_t n = 1)
	{
		if(n == 0)
		{
			return 0;
		}

		if(!mpAdaptor.IsNull())
		{
			while(BufferReader<T>::mBuffer.Size() < n && mpAdaptor->operator()(mpUpStream.Get(), &(this->mBuffer)) > 0)
			{
			}
		}
		return BufferReader<T>::Get(p, n);
	}

	virtual ~ChainReader() throw()
	{
	}

private:
	typename BufferReader<UT>::Ptr mpUpStream;
	typename Adaptor<UT, T>::Ptr mpAdaptor;
};

template<typename T>
class ArrayReader: public ChainReader<T, T>
{
public:
	ArrayReader(const T* ipArray, size_t n)
		: ChainReader<T, T>(NULL, NULL)
	{
		if(ipArray)
		{
			T* lpBuffer = BufferReader<T>::mBuffer.Put(n);
			for(T *lpEnd = lpBuffer + n; lpBuffer < lpEnd;)
			{
				*(lpBuffer++) = *(ipArray++);
			}
		}
	}
};

class ReaderFactory
{
public:
	template<typename UT, typename T>
	static ChainReader<UT, T>* FromAdaptor(Adaptor<UT, T>* ipAdaptor)
	{
		return new ChainReader<UT, T>(NULL, ipAdaptor); 
	}

	template<typename T>
	static ChainReader<T, T>* FromArray(const T* ipArray, size_t n)
	{
		return new ArrayReader<T>(ipArray, n);
	}
};


#endif
