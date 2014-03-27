#ifndef __ADAPTOR_H
#define __ADAPTOR_H

#include "Buffer.h"

namespace MDb
{
namespace Streaming
{

enum StreamStatus
{
	STREAM_START = 0,
	STREAM_RUNNING,
	STREAM_OVER,
	STREAM_DOWNSTREAM_FULL,
	STREAM_UPSTREAM_EMPTY
};

template<class I, class O>
class Adaptor
{
public:
	Adaptor()
		: mStatus(STREAM_START)
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

	virtual void SetStatus(StreamStatus iStatus)
	{
		mStatus = iStatus;
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
		: mTotalInputCount(0)
		, mTotalOutputCount(0)
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

		if(this->mStatus == STREAM_START)
		{
			StreamStart(ipReader, opWriter);
			this->mStatus = STREAM_RUNNING;
		}

		// stream is over, convert the remaining data in upstream
		// call StreamEnd() method
		if(this->mStatus ==  STREAM_OVER)
		{
			I* lpSrc = NULL;
			size_t lInputCount = ipReader->Get(&lpSrc, ipReader->Size());
			size_t lOldWriteBufferCount = opWriter->TotalWriteCount();

			I* lpNewUnitStart = StreamEnd(lpSrc, lpSrc + lInputCount, opWriter);
			size_t lOutputCount = opWriter->TotalWriteCount() - lOldWriteBufferCount;

			mTotalInputCount += lpNewUnitStart - lpSrc;
			mTotalOutputCount += lOutputCount;
			
			ipReader->UnGet(lpSrc + lInputCount - lpNewUnitStart);

			return lOutputCount;
		}

		this->mStatus = STREAM_RUNNING;
		
		// the size of  block is very important
		size_t lInputBlockSize = iInputCount;
		if(iInputCount  == 0 && iOutputCount > 0 && mTotalOutputCount > 0 && mTotalInputCount > 0)
		{
			lInputBlockSize = ceil(1.0 * mTotalInputCount / mTotalOutputCount * iOutputCount);
		}
		lInputBlockSize = lInputBlockSize > mMinBlockSize ? lInputBlockSize: mMinBlockSize;
		lInputBlockSize = lInputBlockSize < mMaxBlockSize ? lInputBlockSize: mMaxBlockSize;

		// get data form input stream
		I* lpSrc = NULL;
		size_t lCount = ipReader->Get(&lpSrc, lInputBlockSize);

		// input stream is running out
		if(lCount == 0)
		{
			this->mStatus = STREAM_UPSTREAM_EMPTY;

			I* lpNewStart = NULL;
			StreamEnd(NULL, NULL, opWriter);
			return 0;
		}

		I* lpEnd = lpSrc + lCount;
		size_t lTotalInputCount = 0;
		size_t lTotalOutputCount = 0;
		for(I* lpUnitStart = lpSrc; lpUnitStart < lpEnd; )
		{
			I* lpUnitEnd = this->FindInputUnit(lpUnitStart, lpEnd);
			// input data is enough to genearte output
 			if(lpUnitEnd > lpUnitStart)
			{
				size_t lOldWriteBufferCount = opWriter->TotalWriteCount();
				I* lpNewUnitStart = this->GenerateOutput(lpUnitStart, lpUnitEnd, opWriter);
				
				size_t lInputCount = lpNewUnitStart - lpUnitStart;
				size_t lOutputCount = opWriter->TotalWriteCount() - lOldWriteBufferCount;

				// output buffer is full
				if(lOutputCount == 0)
				{
					this->mStatus = STREAM_DOWNSTREAM_FULL;
					ipReader->UnGet(lpEnd - lpUnitStart);

					if(mTotalOutputCount == 0 && lTotalOutputCount == 0)
					{
						// bad configuration
						std::wcout << L"bad configuration: output buffer is too small to store data converted from single input unit\n";
					}

					break;
				}

				// we didn't allocate memory for writer yet
				// guess the output size and allocate memory now
				if(lTotalInputCount == 0 && mTotalOutputCount == 0)
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
						this->mStatus = STREAM_UPSTREAM_EMPTY;
						// if input stream is reader, call StreamEnd method
						if(ipReader->Type() == READER)
						{
							size_t lOldWriteBufferCount = opWriter->TotalWriteCount();
							I* lpNewUnitStart = this->StreamEnd(lpUnitStart, lpEnd, opWriter);

							lTotalInputCount += lpNewUnitStart - lpUnitStart;
							lTotalOutputCount += opWriter->TotalWriteCount() - lOldWriteBufferCount;
							lpUnitStart =  lpNewUnitStart;
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

		mTotalOutputCount += lTotalOutputCount;
		mTotalInputCount += lTotalInputCount;
		return lTotalOutputCount;
	}

protected:
	virtual void StreamStart(Buffer<I>* ipReader, Buffer<O>* opWriter)
	{
		return;
	}

	// default implementation is simply restore input
	virtual I* StreamEnd(I* ipStart, I* ipEnd, Buffer<O>* opWriter)
	{
		return ipStart;
	}

	// guess the end of input unit found
	virtual I* FindInputUnit(I* ipStart, I* ipEnd)
	{
		return ipStart;
	}

	virtual I* GenerateOutput(I* ipStart, I* ipEnd, Buffer<O>* opWriter)
	{
		return ipStart;
	}

private:
	size_t mTotalInputCount;
	size_t mTotalOutputCount;
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
	virtual char* GenerateOutput(char* ipStart, char* ipEnd, Buffer<int>* opWriter)
	{
		size_t lOutputcount = (ipEnd - ipStart) / 4;

		int* lpResult = NULL;
		size_t lCount = opWriter->Put(&lpResult, lOutputcount);

		int* lpCurrentResult = lpResult;
		for(char *lpCurrent = ipStart, *lpEnd = ipStart + lCount * 4; lpCurrent < lpEnd; lpCurrentResult++, lpCurrent += 4)
		{
			*lpCurrentResult = *((int*)lpCurrent);
			/**lpCurrentResult =
				(unsigned char)(lpCurrent[3]) * (1 << 24)
				+ (unsigned char)(lpCurrent[2]) * (1 << 16)
				+ (unsigned char)(lpCurrent[1]) * (1 << 8)
				+ (unsigned char)(lpCurrent[0]);*/
		}
		return ipStart + lCount * 4;
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
	virtual int* GenerateOutput(int* ipStart, int* ipEnd, Buffer<char>* opWriter)
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
		return ipStart + lCount / 4;
	}
};

typedef IntToChar CharFromInt;

}
}

#endif
