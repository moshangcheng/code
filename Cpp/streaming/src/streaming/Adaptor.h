#ifndef __ADAPTOR_H
#define __ADAPTOR_H

#include "Reader.h"

template<class I, class O>
struct Adaptor
{
	virtual size_t operator()(BufferReader<I>* ipReader, Buffer<O>* opWriter, size_t iExpectedCount = 1) = 0;

	virtual ~Adaptor() {}
};

template<class I, class O>
struct SimpleAdaptor: public Adaptor<I, O>
{
	SimpleAdaptor()
		: mTotalInputSize(0)
		, mTotalOutputSize(0)
	{}

	size_t operator()(BufferReader<I>* ipReader, Buffer<O>* opWriter, size_t iExpectedCount = 1)
	{
		if(ipReader == NULL || opWriter == NULL || iExpectedCount == 0)
		{
			return 0;
		}

		size_t lInputBlockSize = iExpectedCount;
		if(mTotalOutputSize != 0 && mTotalInputSize != 0)
		{
			lInputBlockSize = ceil(1.0 * mTotalInputSize / mTotalOutputSize * lInputBlockSize);
		}

		I* lpSrc = NULL;
		size_t lCount = ipReader->Get(&lpSrc, lInputBlockSize);

		if(lCount == 0)
		{
			return 0;
		}

		I* lpEnd = lpSrc + lCount;

		size_t lInputCount = 0;
		size_t lOutputCount = 0;
		for(I* lpUnitStart = lpSrc; lpUnitStart < lpEnd; )
		{
			I* lpUnitEnd = this->FindInputUnit(lpUnitStart, lpEnd);
 			if(lpUnitEnd > lpUnitStart)
			{
				// generate output
				lOutputCount += this->GenerateOutput(lpUnitStart, lpUnitEnd, opWriter);
				lInputCount += lpUnitEnd - lpUnitStart;
				lpUnitStart =  lpUnitEnd;
			}
			else
			{
				// input unit not found
				ipReader->UnGet(lpEnd - lpUnitStart);

				if(!lOutputCount)
				{
					// increase input block size and try again
					lInputBlockSize *= 2;

					size_t lNewCount = ipReader->Get(&lpSrc, lInputBlockSize);
					lpEnd = lpSrc + lNewCount;
					lpUnitStart = lpSrc;

					// reach the end of input stream
					// TODO: whether discard incomplete input
					if(lNewCount == lCount)
					{
						// lOutputCount += this->GenerateOutput(lpUnitStart, lpEnd, opWriter);
						// lInputCount += lpEnd - lpUnitStart;
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

		mTotalOutputSize += lOutputCount;
		mTotalInputSize += lInputCount;
		return lOutputCount;
	}

	// return the end of input unit found
	virtual I* FindInputUnit(I* ipStart, I* ipEnd)
	{
		return NULL;
	}

	// return the count outputed elements
	virtual size_t GenerateOutput(I* ipStart, I* ipEnd, Buffer<O>* opWriter)
	{
		return 0;
	}

	virtual ~SimpleAdaptor()
	{
	}

private:
	size_t mTotalInputSize;
	size_t mTotalOutputSize;
};


class CharToInt: public SimpleAdaptor<char, int>
{
public:
	CharToInt() {}

	virtual char* FindInputUnit(char* ipStart, char* ipEnd)
	{
		return ipStart + (ipEnd - ipStart) / 4 * 4;
	}

	// return the count outputed elements
	virtual size_t GenerateOutput(char* ipStart, char* ipEnd, Buffer<int>* opWriter)
	{
		size_t lOutputcount = (ipEnd - ipStart) / 4;

		int* lpResult = NULL;
		size_t lCount = opWriter->Put(&lpResult, lOutputcount);

		int* lpCurrentResult = lpResult;
		for(char* lpCurrent = ipStart; lpCurrent < ipEnd; lpCurrentResult++, lpCurrent += 4)
		{
			*lpCurrentResult = 0;
			for(int i = 3; i >= 0; i--)
			{
				*lpCurrentResult = *lpCurrentResult * 256 + (unsigned char)(lpCurrent[i]);
			}
		}

		return lOutputcount;
	}
};

class IntToChar: public SimpleAdaptor<int, char>
{
public:
	IntToChar() {}

	virtual int* FindInputUnit(int* ipStart, int* ipEnd)
	{
		return ipEnd;
	}

	// return the count outputed elements
	virtual size_t GenerateOutput(int* ipStart, int* ipEnd, Buffer<char>* opWriter)
	{
		size_t lOutputcount = (ipEnd - ipStart) * 4;

		char* lpResult = NULL;
		size_t lCount = opWriter->Put(&lpResult, lOutputcount);

		char* lpCurrentResult = lpResult;
		for(int* lpCurrent = ipStart; lpCurrent < ipEnd; lpCurrent++)
		{
			for(int i = 3, v = *lpCurrent; i >= 0; i--, lpCurrentResult++, v /= 256)
			{
				*lpCurrentResult = (char)(v % 256);
			}
		}

		return lOutputcount;
	}
};

#endif
