#ifndef __ADAPTOR_H__
#define __ADAPTOR_H__

#include "consumer.h"
#include "buffer.h"

template<class I, class O>
struct Adaptor
{
	virtual size_t operator()(Consumer<I>* ipReader, Consumer<O>* opWriter, size_t iExpectedCount = 1) = 0;
};

template<class I, class O>
struct SimpleAdaptor: public Adaptor<I, O>
{
	BasicAdaptor(size_t iInputBlockSize = 1000)
		: mInputBlockSize(iInputBlockSize)
	{}

	size_t operator()(Consumer<I>* ipReader, Consumer<O>* opWriter, size_t iExpectedCount = 1)
	{
		if(ipReader == NULL || opWriter == NULL || iExpectedCount == 0)
		{
			return 0;
		}

		I* lpSrc = NULL;
		size_t lCount = ipReader->Get(&lpSrc, mInputBlockSize);
		I* lpEnd = lpSrc + lCount;

		size_t lInputUnitCount = 0;
		size_t lOutputCount = 0;
		for(I* lpUnitStart = lpSrc; lpUnitStart < lpEnd; )
		{
			I* lpUnitEnd = this->FindInputUnit(lpUnitStart, lpEnd);
			if(lpUnitEnd)
			{
				// generate output
				lOutputCount += this->GenerateOutput(lpUnitStart, lpUnitEnd, opWriter);
			}
			else
			{
				// input unit not found
				ipReader->UnGet(lpEnd - lpUnitStart);

				if(!lUnitCount)
				{
					// increase input block size and try again
					mInputBlockSize *= 2;

					size_t lNewCount = ipReader->Get(&lpSrc, mInputBlockSize);


					// reach the end of input stream
					if(lNewCount == lCount)
					{
						return 0;
					}

					lCount = lNewCount;
					lpEnd = lpSrc + lCount;
				}
				else
				{
					ipReader->Get(&lpSrc, 10000);
				}
			}
		}
	}

	// return the end of input unit found
	virtual I* FindInputUnit(I* ipStart, I* ipEnd)
	{
		return NULL;
	}

	// return the count outputed elements
	virtual size_t GenerateOutput(I* ipStart, I* ipEnd, Consumer<O>* opWriter)
	{
		return 0;
	}

private:
	size_t mInputBlockSize;
};

#endif