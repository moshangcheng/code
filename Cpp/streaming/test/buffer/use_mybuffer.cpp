#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cmath>
using namespace std;

template<typename T>
class Buffer
{
public:
	// constructor for write buffer
	// to reduce initial response time, intial capacity is small
	Buffer(size_t iCapacity)
		: mpData(NULL)
		, mpStart(NULL)
		, mpEnd(NULL)
		, mCapacity(iCapacity)
		, mVersion(0)
	{
		// allocate buffer
		mpData = new T[mCapacity];

		// set status
		mpStart = mpEnd = mpData;

		std::cout << "Write buffer constructor\n";
	}

	// constructor for read buffer
	// to reduce initial response time, intial capacity is small
	Buffer(const T* ipArray, size_t n)
		: mpData(NULL)
		, mpCurrent(NULL)
		, mpEnd(NULL)
		, mCapacity(10)
		, mVersion(0)
	{
		// allocate buffer
		mCapacity = mCapacity < n ? n: mCapacity;
		mpData = new T[mCapacity];

		// set status
		mpCurrent = mpEnd = mpData;

		// copy content
		if(n > 0 && ipArray != NULL)
		{
			mpEnd = mpData + n;
			for(T *lpDest = mpData; lpDest < mpEnd;)
			{
				*(lpDest++) = *(ipArray++);
			}
		}

		std::cout << "Read buffer constructor\n";
	}

	const T* Current() const
	{
		return mpCurrent;
	}

	const T* End() const
	{
		return mpEnd;
	}

	size_t Capacity() const
	{
		return mCapacity;
	}

	size_t Size() const
	{
		return mpEnd - mpCurrent;
	}

	size_t FreeSpaceSize() const
	{
		return mpData + mCapacity - mpEnd;
	}

	void Clear()
	{
		// update version number
		mVersion++;
		mpCurrent = mpEnd = mpData;
	}

	// Get data from buffer
	size_t Get(T** p, size_t n = 1)
	{
		if(n == 0)
		{
			*p = NULL;
			return 0;
		}

		*p = mpCurrent;
		size_t lCount = n < Size() ? n: Size();
		mpCurrent += lCount;
		return lCount;
	}

	// Get the pointer to free space which will be filled by caller
	size_t Put(T** p, size_t n = 1)
	{
		if(n == 0)
		{
			*p = NULL;
			return NULL;
		}

		// try to allocate memory
		More(n);

		*p = mpEnd;
		size_t lCount = n < FreeSpaceSize() ? n: FreeSpaceSize();
		mpEnd += lCount;
		return lCount;
	}

	// Go backward
	bool UnGet(size_t n = 1)
	{
		if(n > mpCurrent - mpData)
		{
			return false;
		}
		mpCurrent -= n;
		return true;
	}

	// Go backward
	bool UnPut(size_t n = 1)
	{
		if(n > Size())
		{
			return false;
		}
		mpEnd -= n;
		return true;
	}

	// used to check validity of pointer returned by Get()/Put()
	// when objects in buffer are rearranged, version number is incremented
	size_t Version() const
	{
		return mVersion;
	}


	// require memory to save more n elements
	void More(size_t n = 0)
	{
		if(mpEnd + n <= mpData + mCapacity)
		{
			return;
		}

		// update version number
		mVersion++;
		
		T* lpNewBuffer = mpData;

		// check buffer capacity
		size_t lExpectedCapacity = n + Size();
		if(lExpectedCapacity > mCapacity)
		{
			std::cout << "--- reallocate buffer " <<  this << " , old buffer size is: " << mCapacity << "\n";
			
			// reallocate memory, use the strategy which is used in string::append and strstreambuf
			mCapacity = (mCapacity / 2 > lExpectedCapacity / 3) ? mCapacity * 3 / 2: lExpectedCapacity;

			std::cout << "--- reallocate buffer " <<  this << " , new buffer size is: " << mCapacity << "\n\n";
			lpNewBuffer = new T[mCapacity];
		}

		// copy
		for(T *i = mpCurrent, *j = lpNewBuffer; i < mpEnd;)
		{
			*(j++) = *(i++);
		}

		// if memory is newly allocated, delete old memory
		if(lpNewBuffer != mpData)
		{
			delete [] mpData;
			mpData = lpNewBuffer;
		}

		//set status
		mpEnd = mpData + (mpEnd - mpCurrent);
		mpCurrent = mpData;
	}

	~Buffer()
	{
		std::cout << "Buffer destructor, version number is: " << mVersion << " \n";

		if(mCapacity > 0 && mpData != NULL)
		{
			delete [] mpData;
			mCapacity = 0;
			mpData = mpCurrent = mpEnd = NULL;
		} 
	}

private:

	T* mpData;
	T* mpCurrent;
	T* mpEnd;

	size_t mCapacity;	
	size_t mVersion;

	Buffer(const Buffer<T>& irBuffer) {}
};



template<typename T>
class Reader
{
public:

	Reader()
	{
		std::cout << "Reader constructor\n";
	}

	// read with copy, caller are responsible to allocate memory
	virtual size_t Read(T* p, size_t n = 1)
	{
		return 0;
	}

	virtual ~Reader() throw()
	{
		std::cout << "Reader destructor\n";
	}
};


template<typename T>
class BufferReader: public Reader<T>
{
public:
	BufferReader(const T* ipArray = NULL, size_t n = 0)
		: mBuffer(ipArray, n)
	{}


	virtual size_t Read(T* p, size_t n = 1)
	{
		T* lpBegin = NULL;
		size_t lCount = mBuffer.Get(&lpBegin, n);

		for(const T* lpEnd = lpBegin + lCount; lpBegin < lpEnd;)
		{
			*(p++) = *(lpBegin++);
		}

		return lCount;
	}

	virtual size_t Get(T** p, size_t n = 1)
	{
		return mBuffer.Get(p, n);
	}

	virtual bool UnGet(size_t n = 1)
	{
		return mBuffer.UnGet(n);
	}

	virtual ~BufferReader() throw()
	{
	}

protected:
	Buffer<T> mBuffer;
};


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


template<typename UT, typename T>
class LinkedReader: public BufferReader<T>
{
public:
	LinkedReader(BufferReader<UT>* ipUpstream, Adaptor<UT, T>* ipAdaptor)
		: mpUpstream(ipUpstream)
		, mpAdaptor(ipAdaptor)
	{}

	LinkedReader(const T* ipArray, size_t iSize)
		: mpUpstream(NULL)
		, mpAdaptor(NULL)
		, BufferReader(ipArray, iSize)
	{}

	template<typename DT>
	LinkedReader<T, DT>* Pipe(Adaptor<T, DT>* ipAdaptor)
	{
		return new LinkedReader<T, DT>(this, ipAdaptor);
	}

	//read with copy, caller are responsible to allocate memory
	virtual size_t Read(T* p, size_t n = 1)
	{
		if(n == 0)
		{
			return 0;
		}

		size_t lCount = BufferReader<T>::Read(p, n);
		if(mpAdaptor)
		{
			while(lCount < n && mpAdaptor->operator()(mpUpstream, &(this->mBuffer), n - lCount) > 0)
			{
				lCount += BufferReader<T>::Read(p + lCount, n - lCount);
			}
		}
		return lCount;
	}

	virtual size_t Get(T** p, size_t n = 1)
	{
		if(n == 0)
		{
			return 0;
		}

		if(mpAdaptor)
		{
			while(this->mBuffer.Size() < n && mpAdaptor->operator()(mpUpstream, &(this->mBuffer), n - this->mBuffer.Size()))
			{
			}
		}
		return BufferReader<T>::Get(p, n);
	}

	~LinkedReader()
	{
		cout << "destructor of linked buffer\n";

		if(mpUpstream)
		{
			delete mpUpstream;
			mpUpstream = NULL;
		}

		if(mpAdaptor)
		{
			delete mpAdaptor;
			mpAdaptor = NULL;
		}
	}

private:
	BufferReader<UT>* mpUpstream;
	Adaptor<UT, T>* mpAdaptor;
};

int main()
{
	{
		clock_t start, end;
		start = clock();

		const int SIZE = 10 * 1000 * 1000;
		int* src = new int[SIZE];
		for(int i = 0; i < SIZE; i++) src[i] = i;

		BufferReader<int> *lpResultBuffer = (new LinkedReader<int, int>(src, SIZE))->Pipe(new IntToChar())->Pipe(new CharToInt());

		int* result = NULL;
		size_t lCount = lpResultBuffer->Get(&result, SIZE);

	

		end = clock();
		cout << "\ntime: " << 1.0 * (end -start) / CLK_TCK << "\n";

		for(size_t i = 0; i < SIZE; i++)
		{
			if(src[i] != result[i])
			{
				cout << "the " << i << " element not equal\n";
				//break;
			}
		}

		delete lpResultBuffer;
		delete [] src;
	}

	{
		std::string lpStr = "abcdefghijklmn";
		char lResult[14];

		BufferReader<char>* lpResultBuffer =  (new LinkedReader<char, char>(lpStr.c_str(), lpStr.length()))->Pipe(new CharToInt())->Pipe(new IntToChar());
	
		size_t lCount = lpResultBuffer->Read(lResult, 14);
		for(size_t i = 0; i < lCount; i++)
		{
			std::cout << lResult[i] << std::endl;
		}
	}
	return 0;
}