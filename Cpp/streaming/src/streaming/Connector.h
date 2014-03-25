#ifndef __CONNECTOR_H
#define __CONNECTOR_H

#include "Buffer.h"
#include "Adaptor.h"

namespace MDb
{
namespace Streaming
{

template<class I, class O>
struct Connector
{
	virtual size_t Run() = 0;

	virtual ~Connector() {}
};

template<class I, class O>
struct SimpleConnector: public Connector<I, O>
{
	SimpleConnector(Buffer<I>* ipReader, Buffer<O>* opWriter, Adaptor<I, O>* ipAdaptor, size_t iBlockSize = MAX_BUFFER_SIZE /sizeof(I))
		: mpReader(ipReader)
		, mpWriter(opWriter)
		, mpAdaptor(ipAdaptor)
		, mBlockSize(iBlockSize)
		, mTotalSize(0)
	{}

	virtual size_t Run()
	{
		if(!mpAdaptor || !mpReader || !mpWriter)
		{
			return 0;
		}

		size_t lTotalSize = 0;

		while(1)
		{
			size_t lCount = (*mpAdaptor)(mpReader, mpWriter, mBlockSize, 0);
			mpWriter->Flush();
			lTotalSize += lCount;
			if(lCount == 0)
			{
				if(mpAdaptor->Status() == UPSTREAM_EMPTY)
				{
					cout << "input buffer is running out\n";
				}
				else
				{
					cout << "output buffer is full\n";
				}
				break;
			}
		}
		mTotalSize += lTotalSize;
		return lTotalSize;
	}

	virtual ~SimpleConnector()
	{
		if(mpReader != NULL)
		{
			delete mpReader;
		}

		if(mpWriter != NULL)
		{
			delete mpWriter;
		}

		if(mpAdaptor != NULL)
		{
			delete mpAdaptor;
		}
	}

private:
	Buffer<I>* mpReader;
	Buffer<O>* mpWriter;
	Adaptor<I, O>* mpAdaptor;
	size_t mBlockSize;
	size_t mTotalSize;
};

}
}

#endif