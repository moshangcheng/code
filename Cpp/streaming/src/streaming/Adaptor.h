#ifndef __ADAPTOR_H
#define __ADAPTOR_H

#include "Buffer.h"

template<class I, class O>
struct Adaptor
{
	virtual size_t operator()(Buffer<I>* ipReader, Buffer<O>* opWriter, size_t iInputCount = 0, size_t iOutputCount = 0) = 0;

	virtual ~Adaptor() {}
};

template<class I, class O>
struct SimpleAdaptor: public Adaptor<I, O>
{
	SimpleAdaptor(size_t iMinBlockSize = 32, size_t iMaxBlockSize = SIZE_MAX)
		: mTotalInputSize(0)
		, mTotalOutputSize(0)
		, mMinBlockSize(iMinBlockSize)
		, mMaxBlockSize(iMaxBlockSize)
	{}

	size_t operator()(Buffer<I>* ipReader, Buffer<O>* opWriter, size_t iInputCount = 0, size_t iOutputCount = 0)
	{
		if(ipReader == NULL || opWriter == NULL)
		{
			return 0;
		}

		// the size of input block is very important
		size_t lInputBlockSize = iInputCount;
		if(iInputCount > 0)
		{
			// use the size speicified by caller
			lInputBlockSize = iInputCount > mMaxBlockSize ? mMaxBlockSize: iInputCount;
		}
		else if(iOutputCount > 0 && mTotalOutputSize > 0 && mTotalInputSize > 0)
		{
			// use the size speicified by calculation
			lInputBlockSize = iOutputCount / mTotalOutputSize > mMaxBlockSize / mTotalInputSize ? mMaxBlockSize: iOutputCount / mTotalOutputSize * mTotalInputSize;
		}
		lInputBlockSize = lInputBlockSize > mMinBlockSize ? lInputBlockSize: mMinBlockSize;
		


		I* lpSrc = NULL;
		size_t lCount = ipReader->Get(&lpSrc, lInputBlockSize);

		if(lCount == 0)
		{
			return 0;
		}

		I* lpEnd = lpSrc + lCount;

		size_t lTotalInputCount = 0;
		size_t lTotalOutputCount = 0;
		for(I* lpUnitStart = lpSrc; lpUnitStart < lpEnd; )
		{
			I* lpUnitEnd = this->FindInputUnit(lpUnitStart, lpEnd);
 			if(lpUnitEnd > lpUnitStart)
			{
				I* lpNewUnitStart = NULL;
				size_t lOutputCount = this->GenerateOutput(lpUnitStart, lpUnitEnd, &lpNewUnitStart, opWriter);
				// output buffer is full
				if(lOutputCount == 0)
				{
					ipReader->UnGet(lpEnd - lpUnitStart);
					break;
				}
				lTotalOutputCount += lOutputCount;
				lTotalInputCount += lpNewUnitStart - lpUnitStart;
				lpUnitStart =  lpNewUnitStart;
				opWriter->Flush();
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
					// TODO: whether discard incomplete input
					if(lNewCount == lCount)
					{
						// lOutputCount += this->GenerateOutput(lpUnitStart, lpEnd, opWriter);
						// lInputCount += lpEnd - lpUnitStart;
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

	// return the end of input unit found
	virtual I* FindInputUnit(I* ipStart, I* ipEnd)
	{
		return NULL;
	}

	// return the end of converted input sequence
	virtual size_t GenerateOutput(I* ipStart, I* ipEnd, I** oppNewStart, Buffer<O>* opWriter)
	{
		return 0;
	}

	virtual ~SimpleAdaptor()
	{
	}

private:
	size_t mTotalInputSize;
	size_t mTotalOutputSize;
	size_t mMinBlockSize;
	size_t mMaxBlockSize;
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
	virtual size_t GenerateOutput(char* ipStart, char* ipEnd, char** oppNewStart, Buffer<int>* opWriter)
	{
		size_t lOutputcount = (ipEnd - ipStart) / 4;

		int* lpResult = NULL;
		size_t lCount = opWriter->Put(&lpResult, lOutputcount);

		int* lpCurrentResult = lpResult;
		for(char* lpCurrent = ipStart, *lpEnd = ipStart + lCount * 4; lpCurrent < lpEnd; lpCurrentResult++, lpCurrent += 4)
		{
			*lpCurrentResult = 0;
			for(int i = 3; i >= 0; i--)
			{
				*lpCurrentResult = *lpCurrentResult * 256 + (unsigned char)(lpCurrent[i]);
			}
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
			for(int i = 3, v = *lpCurrent; i >= 0; i--, lpCurrentResult++, v /= 256)
			{
				*lpCurrentResult = (char)(v % 256);
			}
		}
		*oppNewStart = ipStart + lCount / 4;
		return lCount;
	}
};

typedef IntToChar CharFromInt;

#endif
