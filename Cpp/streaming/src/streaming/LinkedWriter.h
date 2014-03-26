#ifndef __LINKED_WRITER_H
#define __LINKED_WRITER_H


#include "Buffer.h"
#include "Adaptor.h"

namespace MDb
{
namespace Streaming
{

template<typename T, typename DT>
class LinkedWriter: public Buffer<T>
{
public:
	LinkedWriter(Buffer<DT>* ipDownstream, Adaptor<T, DT>* ipAdaptor, size_t iMaxBufferSize = MAX_BUFFER_SIZE /sizeof(T))
		: mpDownstream(ipDownstream)
		, mpAdaptor(ipAdaptor)
		, Buffer<T>(iMaxBufferSize)
	{}

	LinkedWriter(T* p, size_t n)
		: mpDownstream(NULL)
		, mpAdaptor(NULL)
		, Buffer(p, n)
	{}

	template<typename UT>
	LinkedWriter<UT, T>* Pipe(Adaptor<UT, T>* ipAdaptor, size_t iMaxBufferSize = MAX_BUFFER_SIZE /sizeof(UT))
	{
		return new LinkedWriter<UT, T>(this, ipAdaptor, iMaxBufferSize);
	}

	virtual BufferType Type()
	{
		return WRITER;
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
			// to improve perforamnce, dont' use Flush
			// that's to say, flush as late as possible
			while(lCount < n && this->Size() > 0)
			{
				if((*mpAdaptor)(this, mpDownstream, this->Size()) == 0)
				{
					if(mpAdaptor->Status() == DOWNSTREAM_FULL)
					{
						// output buffer is full
						return lCount;
					}
				}
				lCount += Buffer<T>::Write(p + lCount, n - lCount);
			}
		}
		return lCount;
	}

	virtual size_t Put(T** p, size_t n = 1)
	{
		if(n == 0 )
		{
			return n;
		}

		if(mpAdaptor)
		{
			// to improve perforamnce, dont' use Flush
			// that's to say, flush as late as possible
			while(this->FreeSpaceSize() < n && this->Size() > 0)
			{
				if((*mpAdaptor)(this, mpDownstream, this->Size()) == 0)
				{
					if(mpAdaptor->Status() == DOWNSTREAM_FULL)
					{
						// output buffer is full
						*p = NULL;
						return 0;
					}
					else
					{
						// data in input buffer are not enough to generate data in output buffer
						// it't time to fill data in input buffer now
						break;
					}
				}
			}
		}
		return Buffer<T>::Put(p, n);
	}

	bool Flush()
	{
		if(mpAdaptor)
		{
			while(this->Size() && (*mpAdaptor)(this, mpDownstream, this->Size()))
			{
				mpDownstream->Flush();
			}
			return mpAdaptor->Status() == UPSTREAM_EMPTY;
		}
		return false;
	}

	~LinkedWriter()
	{
		std::wcout << "destructor of linked buffer writer\n";

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
	static LinkedWriter<T, T>* ToBuffer()
	{
		return new LinkedWriter<T, T>(NULL, NULL);
	}

	template<typename T>
	static LinkedWriter<T, T>* ToArray(T* p, size_t n)
	{
		return new LinkedWriter<T, T>(p, n);
	}

	template<typename UT, typename T>
	static LinkedWriter<UT, T>* ToAdaptor(Adaptor<UT, T>* ipAdaptor)
	{
		return new LinkedWriter<UT, T>(NULL, ipAdaptor)
	}
};

}
}

#endif
