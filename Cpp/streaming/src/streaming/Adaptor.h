#ifndef __ADAPTOR_H
#define __ADAPTOR_H

#include "Buffer.h"

namespace MDb
{
namespace Streaming
{

enum StreamStatus
{
	ADAPTOR_NORMAL = 0,
	DOWNSTREAM_FULL,
	UPSTREAM_EMPTY
};

template<class I, class O>
class Adaptor
{
public:
	Adaptor()
		: mStatus(ADAPTOR_NORMAL)
	{
	}


	// This method is used to check upstream/downstream status
	// We cannot check their buffer to get status
	// Because upstream/downstream is not one-to-one conversion
	// The data in upstream may not enough to generate data in downstream
	StreamStatus Status() const
	{
		return mStatus;
	}

	virtual size_t operator()(Buffer<I>* ipReader, Buffer<O>* opWriter, size_t iInputCount = 0, size_t iOutputCount = 0)
	{
		return 0;
	}

	virtual ~Adaptor() 
	{
	}

protected:
	StreamStatus mStatus;
};

// add method: BeforeRun(Buffer<I>* ipReader), AfterRun(Buffer<O>* opWriter)
template<class I, class O>
class SimpleAdaptor: public Adaptor<I, O>
{
public:
	SimpleAdaptor(size_t iMinBlockSize = 16, size_t iMaxBlockSize = MAX_BUFFER_SIZE / sizeof(I))
		: mTotalInputSize(0)
		, mTotalOutputSize(0)
		, mMinBlockSize(iMinBlockSize)
		, mMaxBlockSize(iMaxBlockSize)
		, mFirstRun(true)
	{}

	virtual ~SimpleAdaptor()
	{
	}

	size_t operator()(Buffer<I>* ipReader, Buffer<O>* opWriter, size_t iInputCount = 0, size_t iOutputCount = 0)
	{
		if(ipReader == NULL || opWriter == NULL)
		{
			return 0;
		}

		if(mFirstRun)
		{
			StreamStart(ipReader, opWriter);
			mFirstRun = false;
		}
		
		// the size of  block is very important
		size_t lInputBlockSize = iInputCount;
		if(iInputCount  == 0 && iOutputCount > 0 && mTotalOutputSize > 0 && mTotalInputSize > 0)
		{
			lInputBlockSize = ceil(1.0 * mTotalInputSize / mTotalOutputSize * iOutputCount);
			lInputBlockSize = lInputBlockSize < mMaxBlockSize ? lInputBlockSize: mMaxBlockSize;
		}
		lInputBlockSize = lInputBlockSize > mMinBlockSize ? lInputBlockSize: mMinBlockSize;

		// get data form input stream
		I* lpSrc = NULL;
		size_t lCount = ipReader->Get(&lpSrc, lInputBlockSize);

		// input stream is running out
		if(lCount == 0)
		{
			this->mStatus = UPSTREAM_EMPTY;

			I* lpNewStart = NULL;
			StreamEnd(NULL, NULL, &lpNewStart, opWriter);
			return 0;
		}

		I* lpEnd = lpSrc + lCount;
		size_t lTotalInputCount = 0;
		size_t lTotalOutputCount = 0;
		for(I* lpUnitStart = lpSrc; lpUnitStart < lpEnd; )
		{
			I* lpUnitEnd = this->FindInputUnit(lpUnitStart, lpEnd);
 			if(lpUnitEnd)
			{
				I* lpNewUnitStart = NULL;
				size_t lOutputCount = this->GenerateOutput(lpUnitStart, lpUnitEnd, &lpNewUnitStart, opWriter);
				size_t lInputCount = lpNewUnitStart - lpUnitStart;

				// output buffer is full
				if(lOutputCount == 0)
				{
					// if output stream is reader
					// its buffer is not large enough to store data converted from one input unit
					// if output stream is writer, set status
					if(opWriter->Type() == WRITER)
					{
						this->mStatus = DOWNSTREAM_FULL;
					}
					ipReader->UnGet(lpEnd - lpUnitStart);
					break;
				}

				// we didn't allocate memory for writer yet
				// guess the output size and allocate memory now
				if(lTotalInputCount == 0 && mTotalOutputSize == 0)
				{
					opWriter->More(ceil(1.0 * lOutputCount / lInputCount * (lInputBlockSize - lInputCount)));
				}

				lTotalOutputCount += lOutputCount;
				lTotalInputCount += lInputCount;
				lpUnitStart =  lpNewUnitStart;
			}
			else
			{
				// input unit not found
				ipReader->UnGet(lpEnd - lpUnitStart);

				if(!lTotalOutputCount)
				{
					// increase input block size and try again
					lInputBlockSize *= 2;

					size_t lNewCount = ipReader->Get(&lpSrc, lInputBlockSize);
					lpEnd = lpSrc + lNewCount;
					lpUnitStart = lpSrc;

					// reach the end of input stream
					if(lNewCount == lCount)
					{
						// if input stream is writer, all data in its buffer is not enough to generate output in output stream
						// if input stream is reader, call StreamEnd method
						if(ipReader->Type() == READER)
						{
							I* lpNewUnitStart = NULL;
							size_t lOutputCount = this->StreamEnd(lpUnitStart, lpEnd, &lpNewUnitStart, opWriter);

							lTotalOutputCount += lOutputCount;
							lTotalInputCount += lpNewUnitStart - lpUnitStart;
							lpUnitStart =  lpNewUnitStart;
							this->mStatus = UPSTREAM_EMPTY;
						}
						ipReader->UnGet(lpEnd - lpUnitStart);
						break;
					}

					lCount = lNewCount;
				}
				else
				{
					break;
				}
			}
		}

		mTotalOutputSize += lTotalOutputCount;
		mTotalInputSize += lTotalInputCount;
		return lTotalOutputCount;
	}

protected:
	virtual void StreamStart(Buffer<I>* ipReader, Buffer<O>* opWriter)
	{
		return;
	}

	// default implementation is simply restore input
	virtual size_t StreamEnd(I* ipStart, I* ipEnd, I** oppNewStart, Buffer<O>* opWriter)
	{
		if(oppNewStart != NULL)
		{
			*oppNewStart = ipStart;
		}
		return 0;
	}

	// guess the end of input unit found
	virtual I* FindInputUnit(I* ipStart, I* ipEnd)
	{
		return NULL;
	}

	virtual size_t GenerateOutput(I* ipStart, I* ipEnd, I** oppNewStart, Buffer<O>* opWriter)
	{
		return 0;
	}

private:
	size_t mTotalInputSize;
	size_t mTotalOutputSize;
	size_t mMinBlockSize;
	size_t mMaxBlockSize;

	bool mFirstRun;
};


class CharToInt: public SimpleAdaptor<char, int>
{
public:
	CharToInt() {}

protected:
	virtual char* FindInputUnit(char* ipStart, char* ipEnd)
	{
		return ipStart + (ipEnd - ipStart) / 4 * 4;
	}

	// return the count outputed elements
	virtual size_t GenerateOutput(char* ipStart, char* ipEnd, char** oppNewStart, Buffer<int>* opWriter)
	{
		size_t lOutputcount = (ipEnd - ipStart) / 4;

		int* lpResult = NULL;
		size_t lCount = opWriter->Put(&lpResult, lOutputcount);

		int* lpCurrentResult = lpResult;
		for(char* lpCurrent = ipStart, *lpEnd = ipStart + lCount * 4; lpCurrent < lpEnd; lpCurrentResult++, lpCurrent += 4)
		{
			*lpCurrentResult = *((int*)lpCurrent);
			/**lpCurrentResult =
				(unsigned char)(lpCurrent[3]) * (1 << 24)
				+ (unsigned char)(lpCurrent[2]) * (1 << 16)
				+ (unsigned char)(lpCurrent[1]) * (1 << 8)
				+ (unsigned char)(lpCurrent[0]);*/
		}
		*oppNewStart = ipStart + lCount * 4;
		return lCount;
	}
};

typedef CharToInt IntFromChar;

class IntToChar: public SimpleAdaptor<int, char>
{
public:
	IntToChar() {}

protected:
	virtual int* FindInputUnit(int* ipStart, int* ipEnd)
	{
		return ipEnd;
	}

	// return the count outputed elements
	virtual size_t GenerateOutput(int* ipStart, int* ipEnd, int** oppNewStart, Buffer<char>* opWriter)
	{
		size_t lOutputcount = (ipEnd - ipStart) * 4;

		char* lpResult = NULL;
		size_t lCount = opWriter->Put(&lpResult, lOutputcount);
		opWriter->UnPut(lCount % 4);
		lCount = lCount / 4  * 4;

		char* lpCurrentResult = lpResult;
		for(int* lpCurrent = ipStart, *lpEnd = ipStart + lCount / 4; lpCurrent < lpEnd; lpCurrent++)
		{
			memcpy(lpCurrentResult, lpCurrent, sizeof(int));
			lpCurrentResult += 4;
			/*int v = *lpCurrent;
			*lpCurrentResult++ = (char)(v & 255);
			*lpCurrentResult++ = (char)((v >> 8) & 255);
			*lpCurrentResult++ = (char)((v >> 16) & 255);
			*lpCurrentResult++ = (char)(v >> 24);*/
		}
		*oppNewStart = ipStart + lCount / 4;
		return lCount;
	}
};

typedef IntToChar CharFromInt;

}
}

#endif
