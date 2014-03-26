#ifndef __CONNECTOR_H
#define __CONNECTOR_H

#include "Buffer.h"
#include "Adaptor.h"

namespace MDb
{
namespace Streaming
{

template<class I, class O>
class Connector
{
public:
	virtual size_t Run()
	{
		return 0;
	}

	StreamStatus Status()
	{
		return mStatus;
	}

	virtual ~Connector() {}

protected:
	StreamStatus mStatus;
};

template<class I, class O>
class SimpleConnector: public Connector<I, O>
{
public:
	SimpleConnector(Buffer<I>* ipReader, Buffer<O>* opWriter, Adaptor<I, O>* ipAdaptor, size_t iBlockSize = MAX_BUFFER_SIZE /sizeof(I))
		: mpReader(ipReader)
		, mpWriter(opWriter)
		, mpAdaptor(ipAdaptor)
		, mBlockSize(iBlockSize)
		, mTotalSize(0)
	{}

	virtual ~SimpleConnector()
	{
		if(mpReader != NULL)
		{
			delete mpReader;
			mpReader = NULL;
		}

		if(mpWriter != NULL)
		{
			delete mpWriter;
			mpWriter = NULL;
		}

		if(mpAdaptor != NULL)
		{
			delete mpAdaptor;
			mpAdaptor = NULL;
		}
	}

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
			lTotalSize += lCount;
			if(lCount == 0)
			{
				if(mpAdaptor->Status() == UPSTREAM_EMPTY)
				{
					mpWriter->Flush();
					this->mStatus = UPSTREAM_EMPTY;
					std::wcout << "input buffer is running out\n";
				}
				else
				{
					this->mStatus = DOWNSTREAM_FULL;
					std::wcout << "output buffer is full\n";
				}
				break;
			}
		}
		mTotalSize += lTotalSize;
		return lTotalSize;
	}

private:
	Buffer<I>* mpReader;
	Buffer<O>* mpWriter;
	Adaptor<I, O>* mpAdaptor;
	size_t mBlockSize;
	size_t mTotalSize;
};

// improver performance by doing copy in node has least elements
// e.g. Copy(int, int<-char<-bool) is much quicker than Copy(int->char->bool, bool)
template<class T>
class CopyConnector: public Connector<T, T>
{
public:
	CopyConnector(Buffer<T>* ipReader, Buffer<T>* opWriter, size_t iBlockSize = MAX_BUFFER_SIZE /sizeof(T))
		: mpReader(ipReader)
		, mpWriter(opWriter)
		, mBlockSize(iBlockSize)
		, mTotalSize(0)
	{}

	virtual ~CopyConnector()
	{
		if(mpReader != NULL)
		{
			delete mpReader;
			mpReader = NULL;
		}

		if(mpWriter != NULL)
		{
			delete mpWriter;
			mpWriter = NULL;
		}
	}

	virtual size_t Run()
	{
		if(!mpReader || !mpWriter)
		{
			return 0;
		}

		size_t lTotalSize = 0;

		while(1)
		{
			T* lpSrc = NULL;
			size_t lOutputCount = mpWriter->Put(&lpSrc, mBlockSize);
			if(lOutputCount == 0)
			{
				this->mStatus = DOWNSTREAM_FULL;
				cout << "output buffer is full\n";
				break;
			}

			size_t lInputCount = mpReader->Read(lpSrc, lOutputCount);
			if(lInputCount < lOutputCount)
			{
				mpWriter->UnPut(lOutputCount - lInputCount);
				mpWriter->Flush();
				this->mStatus = UPSTREAM_EMPTY;
				cout << "input buffer is runnning out\n";
				break;
			}

			lTotalSize += lInputCount;
		}
		mTotalSize += lTotalSize;
		return lTotalSize;
	}

private:
	Buffer<T>* mpReader;
	Buffer<T>* mpWriter;
	size_t mBlockSize;
	size_t mTotalSize;
};

// improver performance by doing copy in node has least elements
// e.g. Copy(int, int<-char<-bool) is much quicker than Copy(int->char->bool, bool)
template<class T>
class MTCopyConnector: public Connector<T, T>
{
public:
	MTCopyConnector(Buffer<T>* ipReader, Buffer<T>* opWriter, size_t lThreadCount, size_t iBlockSize = MAX_BUFFER_SIZE /sizeof(T))
		: mpReader(ipReader)
		, mpWriter(opWriter)
		, mBlockSize(iBlockSize)
		, mTotalSize(0)
	{}

	virtual ~MTCopyConnector()
	{
		if(mpReader != NULL)
		{
			delete mpReader;
			mpReader = NULL;
		}

		if(mpWriter != NULL)
		{
			delete [] mpWriter;
			mpWriter = NULL;
		}
	}

	virtual size_t Run()
	{
		if(!mpReader || !mpWriter)
		{
			return 0;
		}

		size_t lTotalSize = 0;

		while(1)
		{
			T* lpSrc = NULL;
			size_t lOutputCount = mpWriter->Put(&lpSrc, mBlockSize);
			if(lOutputCount == 0)
			{
				this->mStatus = DOWNSTREAM_FULL;
				cout << "output buffer is full\n";
				break;
			}

			size_t lInputCount = mpReader->Read(lpSrc, lOutputCount);
			if(lInputCount < lOutputCount)
			{
				mpWriter->UnPut(lOutputCount - lInputCount);
				mpWriter->Flush();
				this->mStatus = UPSTREAM_EMPTY;
				cout << "input buffer is runnning out\n";
				break;
			}

			lTotalSize += lInputCount;
		}
		mTotalSize += lTotalSize;
		return lTotalSize;
	}

private:
	Buffer<T>* mpReader;
	Buffer<T>* mpWriter;
	size_t mThreadCount;
	size_t mBlockSize;
	size_t mTotalSize;
};

}
}

#endif