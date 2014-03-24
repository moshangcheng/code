#ifndef __LINKED_WRITER_H
#define __LINKED_WRITER_H


#include "Buffer.h"
#include "Adaptor.h"


template<typename T, typename DT>
class LinkedWriter: public Buffer<T>
{
public:
	LinkedWriter(T* p, size_t n)
		: mpDownstream(NULL)
		, mpAdaptor(NULL)
		, Buffer(p, n)
	{}

	LinkedWriter(Buffer<DT>* ipDownstream, Adaptor<T, DT>* ipAdaptor)
		: mpDownstream(ipDownstream)
		, mpAdaptor(ipAdaptor)
	{}

	template<typename UT>
	LinkedWriter<UT, T>* Pipe(Adaptor<UT, T>* ipAdaptor)
	{
		return new LinkedWriter<UT, T>(this, ipAdaptor);
	}

	virtual size_t Write(T* p, size_t n = 1)
	{
		if(n == 0)
		{
			return 0;
		}

		size_t lCount = Buffer<T>::Write(p, n);
		if(mpAdaptor)
		{
			while(lCount < n && mpAdaptor->operator()(this, mpDownstream, this->Size()) > 0)
			{
				lCount += Buffer<T>::Write(p + lCount, n - lCount);
			}
		}
		return lCount;
	}

	void Flush()
	{
		if(mpAdaptor)
		{
			while(this->Size() && mpAdaptor->operator()(this, mpDownstream, this->Size()))
			{
			}
		}
		if(mpDownstream)
		{
			mpDownstream->Flush();
		}
	}

	~LinkedWriter()
	{
		cout << "destructor of linked buffer writer\n";

		if(mpDownstream)
		{
			delete mpDownstream;
			mpDownstream = NULL;
		}

		if(mpAdaptor)
		{
			delete mpAdaptor;
			mpAdaptor = NULL;
		}
	}

private:
	Buffer<DT>* mpDownstream;
	Adaptor<T, DT>* mpAdaptor;
};


class WriterFactory
{
public:
	template<typename T>
	static LinkedWriter<T, T>* ToArray(T* p, size_t n = SIZE_MAX)
	{
		return new LinkedWriter<T, T>(p, n);
	}

	template<typename UT, typename T>
	static LinkedWriter<UT, T>* ToAdaptor(Adaptor<UT, T>* ipAdaptor)
	{
		return new LinkedWriter<UT, T>(NULL, ipAdaptor)
	}
};

#endif
