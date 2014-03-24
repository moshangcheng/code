#ifndef __CONNECTOR_H
#define __CONNECTOR_H

#include "Buffer.h"

template<class T>
struct Connector
{
	virtual size_t Run() = 0;

	virtual ~Connector() {}
};

template<class T>
struct SimpleConnector: public Connector<T>
{
	SimpleConnector(Buffer<T>* ipInput, Buffer<T>* ipOutput, size_t iBlockSize = 64 * 1024)
		: mpInput(ipInput)
		, mpOutput(ipOutput)
		, mBlockSize(iBlockSize)
		, mTotalSize(0)
	{}

	virtual size_t Run()
	{
		size_t lTotalSize = 0;
		while(1)
		{
			T* lpSrc = NULL;
			size_t lSrcCount = mpInput->Get(&lpSrc, mBlockSize);
			lTotalSize += lSrcCount;
			if(lSrcCount == 0)
			{
				cout << "input buffer is running out\n";
				break;
			}

			while(lSrcCount > 0)
			{
				T* lpResult = NULL;
				size_t lResultCount = mpOutput->Put(&lpResult, lSrcCount);
				if(lResultCount == 0)
				{
					break;
				}
				lSrcCount -= lResultCount;

				for(T* lpResultEnd = lpResult + lResultCount; lpResult < lpResultEnd; )
				{
					*(lpResult++) = *(lpSrc++);
				}
				mpOutput->Flush();
			}

			lTotalSize -= lSrcCount;
			mpInput->UnGet(lSrcCount);
			if(lSrcCount > 0)
			{
				cout << "output buffer is full\n";
				break;
			}
		}
		mTotalSize += lTotalSize;
		return lTotalSize;
	}

	virtual ~SimpleConnector() {}

private:
	Buffer<T>* mpInput;
	Buffer<T>* mpOutput;
	size_t mBlockSize;
	size_t mTotalSize;
};


#endif