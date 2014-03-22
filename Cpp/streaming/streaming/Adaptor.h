#ifndef __ADAPTOR_H
#define __ADAPTOR_H

#include "../streaming/Reader.h"
#include "../streaming/Writer.h"

template<typename I, typename O>
class Adaptor
{
public:

	Adaptor()
	{
		std::cout << "Adaptor constructor\n";
	}

	virtual size_t operator() (BufferReader<I>* ipReader, BufferWriter<O>* opWriter, size_t iExpectedCount = 1)
	{
		return 0;
	}

	virtual ~Adaptor() throw()
	{
		std::cout << "Adaptor destructor\n";
	}

};


class BoolToChar: public Adaptor<bool, char>
{
public:
	size_t operator() (BufferReader<bool>* ipReader, BufferWriter<char>* opWriter, size_t iExpectedCount = 1)
	{
		if(ipReader == NULL)
		{
			return 0;
		}

		// read data from upstream
		const bool* lpSrc = NULL;
		size_t lCount = ipReader->Get(&lpSrc, 8 * iExpectedCount);

		// upstream is running out
		if(lCount == 0)
		{
			return 0;
		}

		const bool* lInputIndex = lpSrc;
		const bool* lInputEnd = lpSrc + lCount - 7;

		// prepare output buffer
		opWriter->More(lCount / 8);

		// conversion
		size_t lOutputCount = 0;
		for(; lInputIndex < lInputEnd; lOutputCount++, lInputIndex += 8)
		{
			// get write buffer
			char* lpResult = opBuffer->Put(iExpectedCount);
			for(int i = 7, *lpResult = 0; i >= 0; i--)
			{
				*lpResult = *lpResult * 2 + lInputIndex[i];
			}
		}

		if(lOutputCount > 0)
		{
			// restore not parsed elements in upstream
			ipReader->UnGet(lInputEnd - lInputIndex);
		}
		else
		{

		}

		return lOutputCount;
	}
};

class CharToBool: public Adaptor<char, bool>
{
	size_t operator() (BufferReader<char>* ipReader, BufferWriter<bool>* opWriter, size_t iExpectedCount = 1)
	{
		if(ipReader == NULL)
		{
			return 0;
		}

		// read data from upstream
		const char* lpSrc = NULL;
		size_t lCount = ipReader->Get(&lpSrc);

		if(lCount < 1)
		{
			return 0;
		}

		// get write buffer
		bool* lpResult = opWriter->Put(8);

		// conversion
		for(int i = 0; i < 8; i++)
		{
			lpResult[i] = ((*lpSrc) & (1 << i)) > 0;
		}
		
		return 8;
	}
};

class CharToInt: public Adaptor<char, int>
{
	size_t operator() (BufferReader<char>* ipReader, BufferWriter<int>* opWriter, size_t iExpectedCount = 1)
	{
		if(ipReader == NULL)
		{
			return 0;
		}

		// read data from upstream
		const char* lpSrc = NULL;
		size_t lCount = ipReader->Get(&lpSrc, 4);

		if(lCount < 4)
		{
			return 0;
		}

		// get write buffer
		int* lpResult = opWriter->Put();


		// conversion
		for(int i = 3; i >= 0; i--)
		{
			*lpResult = *lpResult * 256 + lpSrc[i];
		}
		
		return 1;
	}
};

class IntToChar: public Adaptor<int, char>
{
public:
	size_t operator() (BufferReader<int>* ipReader, BufferWriter<char>* opWriter, size_t iExpectedCount = 1)
	{
		if(ipReader == NULL)
		{
			return 0;
		}

		// read data from upstream
		const int* lpSrc = NULL;
		size_t lCount = ipReader->Get(&lpSrc);

		if(lCount < 1)
		{
			return 0;
		}

		char* lpResult = opWriter->Put(4);

		// conversion
		for(int i = 0, v = *lpSrc; i < 4; i++, v /= 256)
		{
			lpResult[i] = (char)(v % 256);
		}
		
		return 4;
	}
};


class IntToDouble: public Adaptor<int, double>
{
	size_t operator() (BufferReader<int>* ipReader, BufferWriter<double>* opWriter, size_t iExpectedCount = 1)
	{
		if(ipReader == NULL)
		{
			return 0;
		}

		// read data from upstream
		const int* lpSrc = NULL;
		size_t  lCount = ipReader->Get(&lpSrc);

		if(lCount < 1)
		{
			return 0;
		}

		double* lpResult = opWriter->Put();

		//conversion
		*lpResult = *lpSrc;

		return 1;
	}
};

#endif
