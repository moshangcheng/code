#ifndef __CONNECTOR_H
#define __CONNECTOR_H

#include "Buffer.h"
#include "Adaptor.h"

template<class I, class O>
struct Connector
{
	virtual size_t Run() = 0;

	virtual ~Connector() {}
};

template<class I, class O>
struct SimpleConnector: public Connector<I, O>
{
	SimpleConnector(Buffer<I>* ipReader, Buffer<O>* opWriter, Adaptor<I, O>* ipAdaptor, size_t iBlockSize = 64 * 1024)
		: mpReader(ipReader)
		, mpWriter(opWriter)
		, mpAdaptor(ipAdaptor)
		, mBlockSize(iBlockSize)
		, mTotalSize(0)
	{}

	virtual size_t Run()
	{
		if(!mpAdaptor || !mpInput || !mpOutput)
		{
			return 0;
		}

		size_t lTotalSize = 0;

		while(1)
		{
			size_t lCount = mpAdaptor->operator()(mpReader, mpWriter, mBlockSize, 0);
			if(lCount == 0)
			{
				if(mpWriter->FreeSpaceSize() || mpReader->Size() == 0)
				{
					cout << "input buffer is running out\n";
				}
				else
				{
					cout << "output buffer is full\n";
				}
				break;
			}
			lTotalSize += lCount;
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


#endif