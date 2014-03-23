#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

template<class I, class O>
struct Adaptor
{
	virtual size_t operator()(basic_stringbuf<I>* ipReader, basic_stringbuf<O>* opWriter, size_t iExpectedCount = 1) = 0;

	virtual ~Adaptor() {}
};

template<class I, class O>
struct SimpleAdaptor: public Adaptor<I, O>
{
	SimpleAdaptor(size_t iInputBlockSize = 1000)
		: mInputBlockSize(iInputBlockSize)
		, mTotalInputSize(0)
		, mTotalOutputSize(0)
		, mInputBuffer(NULL)
	{
		mInputBuffer = new I[mInputBlockSize];
	}

	size_t operator()(basic_stringbuf<I>* ipReader, basic_stringbuf<O>* opWriter, size_t iExpectedCount = 1)
	{
		if(ipReader == NULL || opWriter == NULL || iExpectedCount == 0)
		{
			return 0;
		}

		size_t lCount = ipReader->sgetn(mInputBuffer, mInputBlockSize);

		if(lCount == 0)
		{
			return 0;
		}

		I* lpEnd = mInputBuffer + lCount;

		size_t lInputCount = 0;
		size_t lOutputCount = 0;
		for(I* lpUnitStart = mInputBuffer; lpUnitStart < lpEnd; )
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
				ipReader->pubseekoff(lpUnitStart - lpEnd, ios_base::cur, ios_base::in);

				if(!lOutputCount)
				{
					delete [] mInputBuffer;
					// increase input block size and try again
					mInputBlockSize *= 2;
					mInputBuffer = new I[mInputBlockSize];

					size_t lNewCount = ipReader->sgetn(mInputBuffer, mInputBlockSize);
					lpEnd = mInputBuffer + lNewCount;
					lpUnitStart = mInputBuffer;

					// reach the end of input stream
					if(lNewCount == lCount)
					{
						lOutputCount += this->GenerateOutput(lpUnitStart, lpEnd, opWriter);
						lInputCount += lpEnd - lpUnitStart;
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
	virtual size_t GenerateOutput(I* ipStart, I* ipEnd, basic_stringbuf<O>* opWriter)
	{
		return 0;
	}

	virtual ~SimpleAdaptor()
	{
		if(mInputBuffer != NULL)
		{
			delete [] mInputBuffer;
		}
	}

private:
	size_t mTotalInputSize;
	size_t mTotalOutputSize;

	size_t mInputBlockSize;
	I* mInputBuffer;
};


class CharToInt: public SimpleAdaptor<char, int>
{
public:
	CharToInt(): SimpleAdaptor<char, int>(100 * 1000) {}

	virtual char* FindInputUnit(char* ipStart, char* ipEnd)
	{
		return ipStart + (ipEnd - ipStart) / 4 * 4;
	}

	// return the count outputed elements
	virtual size_t GenerateOutput(char* ipStart, char* ipEnd, basic_stringbuf<int>* opWriter)
	{
		size_t lOutputcount = (ipEnd - ipStart) / 4;

		int *lpResult = new int[lOutputcount];

		int* lpCurrentResult = lpResult;
		for(char* lpCurrent = ipStart; lpCurrent < ipEnd; lpCurrentResult++, lpCurrent += 4)
		{
			*lpCurrentResult = 0;
			for(int i = 3; i >= 0; i--)
			{
				*lpCurrentResult = *lpCurrentResult * 256 + (unsigned char)lpCurrent[i];
			}
		}

		opWriter->sputn(lpResult, lOutputcount);
		delete [] lpResult;

		return lOutputcount;
	}
};

class IntToChar: public SimpleAdaptor<int, char>
{
public:
	IntToChar(): SimpleAdaptor<int, char>(25 * 1000) {}

	virtual int* FindInputUnit(int* ipStart, int* ipEnd)
	{
		return ipEnd;
	}

	// return the count outputed elements
	virtual size_t GenerateOutput(int* ipStart, int* ipEnd, basic_stringbuf<char>* opWriter)
	{
		size_t lOutputcount = (ipEnd - ipStart) * 4;

		char *lpResult = new char[lOutputcount];

		char* lpCurrentResult = lpResult;
		for(int* lpCurrent = ipStart; lpCurrent < ipEnd; lpCurrent++)
		{
			for(int i = 3, v = *lpCurrent; i >= 0; i--, lpCurrentResult++, v /= 256)
			{
				*lpCurrentResult = (char)(v % 256);
			}
		}

		opWriter->sputn(lpResult, lOutputcount);
		delete [] lpResult;

		return lOutputcount;
	}
};


template<typename UT, typename T>
class LinkedReader: public basic_stringbuf<T>
{
public:
	LinkedReader(basic_stringbuf<UT>* ipPrevBuffer, Adaptor<UT, T>* ipAdaptor)
		: mpPrevBuffer(ipPrevBuffer)
		, mpAdaptor(ipAdaptor)
	{}

	LinkedReader(const T* ipArray, size_t iSize)
		: mpPrevBuffer(NULL)
		, mpAdaptor(NULL)
		, basic_stringbuf(basic_string<T>(ipArray, iSize))
	{}

	template<typename DT>
	LinkedReader<T, DT>* Pipe(Adaptor<T, DT>* ipAdaptor)
	{
		return new LinkedReader<T, DT>(this, ipAdaptor);
	}

	int_type underflow()
	{
		// read from buffer
		int_type c = basic_stringbuf<T>::underflow();
		if(c == EOF)
		{
			// read from upstream
			if(mpAdaptor != NULL && mpPrevBuffer != NULL && mpAdaptor->operator()(mpPrevBuffer, this) > 0)
			{
				return *(this->gptr());
			}
		}
		return c;
	}

	/*int_type overflow()
	{
		return basic_stringbuf<T>::overflow();
	}*/

	~LinkedReader()
	{
		cout << "destructor of linked buffer\n";

		if(mpPrevBuffer)
		{
			delete mpPrevBuffer;
			mpPrevBuffer = NULL;
		}

		if(mpAdaptor)
		{
			delete mpAdaptor;
			mpAdaptor = NULL;
		}
	}

private:
	basic_stringbuf<UT>* mpPrevBuffer;
	Adaptor<UT, T>* mpAdaptor;
};

int main()
{
	clock_t start, end;
	start = clock();

	const int SIZE = 10 * 1000 * 1000;
	int* src = new int[SIZE];
	int* result = new int[SIZE];
	for(int i = 0; i < SIZE; i++) src[i] = i;

	basic_stringbuf<int> *lpResultBuffer = (new LinkedReader<int, int>(src, SIZE))->Pipe(new IntToChar())->Pipe(new CharToInt());

	lpResultBuffer->sgetn(result, SIZE);

	


	end = clock();
	cout << "\ntime: " << 1.0 * (end -start) / CLK_TCK << "\n";

	for(size_t i = 0; i < SIZE; i++)
	{
		if(src[i] != result[i])
		{
			cout << "the " << i << " element not equal\n";
			break;
		}
	}

	delete lpResultBuffer;
	delete [] src;
	delete [] result;

	return 0;
}