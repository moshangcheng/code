#ifndef __LINKER_H
#define __LINKER_H

#include "adaptor.h"

template<typename UT, typename T>
class LinkedReader: public Consumer<T>
{
public:
	LinkedReader(Consumer<UT>* ipUpstream, Adaptor<UT, T>* ipAdaptor)
		: mpReader(ipUpstream)
		, mpAdaptor(ipAdaptor)
	{
		mpWriter = mpBuffer->GerWriter();
	}

	template<typename DT>
	LinkedReader<T, DT>* Pipe(Adaptor<T, DT>* ipAdaptor)
	{
		return new LinkedReader<T, DT>(mpBuffer->GetReader(), ipAdaptor);
	}

	size_t Get(T** p, size_t n = 1)
	{
		if(n == 0)
		{
			return 0;
		}

		if(mpAdaptor)
		{
			Consumer<T>* lpWriter = mpBuffer->GetWriter();
			while(Consumer<T>::Size() < n && (*mpAdaptor)()(mpUpstream, lpWriter) > 0)
			{
			}
		}
		return Consumer<T>::Get(p, n);
	}

	size_t UnGet(size_t n = 1)
	{
		return 0;
	}

private:
	Buffer<T>* mpBuffer;
	Consumer<UT>* mpReader;
	Adaptor<UT, T>* mpAdaptor;
};

template<typename UT, typename T>
class LinkedWriter: public Consumer<T>
{
public:
	LinkedWriter(Consumer<UT>* ipUpstream, Adaptor<UT, T>* ipAdaptor)
		: mpUpstream(ipUpstream)
		, mpAdaptor(ipAdaptor)
	{}

	template<typename DT>
	LinkedWriter<T, DT>* Pipe(Adaptor<T, DT>* ipAdaptor)
	{
		return new LinkedWriter<T, DT>(mpBuffer->GerWriter(), ipAdaptor);
	}

	size_t Get(T** p, size_t n = 1)
	{
		if(n > this->Size())
		{
			mpBuffer->More(n);
		}
		return n;
	}

	size_t UnGet(size_t n = 1)
	{
		return 0;
	}

private:
	Buffer<T>* mpBuffer;
	Consumer<UT>* mpUpstream;
	Adaptor<UT, T>* mpAdaptor;
};

#endif