#include <iostream>
using namespace std;



// read and write are dual operations
// read is operation of occupied space
// write is operation of not occupied space

// see implementation of streambuf in VC2010
// std::basic_stringbuf is a good choic if std:move in C++11 used

// It should be much easier in golang

template<typename T>
class Consumer
{
public:

	Consumer(T** ippData, T** ippStart, T** ippEnd)
		: mppData(ippData)
		, mppStart(ippStart)
		, mppEnd(ippEnd)
	{}

	const T* Start() const
	{
		return *mppStart;
	}

	const T* End() const
	{
		return *mppEnd;
	}

	size_t Size() const
	{
		return (*mppEnd) - (*mppStart);
	}

	size_t Get(T** p, size_t n = 1)
	{
		if(n == 0)
		{
			*p = NULL;
			return 0;
		}

		*p = *mppStart;
		size_t lCount = n < Size() ? n: Size();
		*mppStart += lCount;
		return lCount;
	}

	// Go backward
	bool UnGet(size_t n = 1)
	{
		if(n > Size())
		{
			return false;
		}
		*mppStart -= n;
		return true;
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
		for(T *i = mpStart, *j = lpNewBuffer; i < mpEnd;)
		{
			*(j++) = *(i++);
		}

		// if memory is newly allocated, delete old memory
		if(lpNewBuffer != mpData)
		{
			delete [] mpData;
			mpData = mpData;
		}

		//set status
		mpEnd = mpData + (mpEnd - mpStart);
		mpStart = mpData;
	}

private:
	T** mppData;
	T** mppStart;
	T** mppEnd;
};

template<typename T>
struct Buffer
{
	Buffer(size_t iCapacity)
		: mpData(NULL)
		, mpStart(NULL)
		, mpEnd(NULL)
		, mpDataEnd(NULL)
		, mVersion(0)
	{
		// allocate buffer
		mpData = new T[iCapacity];

		// set status
		mpStart = mpEnd = mpData;
		mpDataEnd = mpData + iCapacity;

		std::cout << "Write buffer constructor\n";
	}

	Buffer(const T* ipArray = NULL, size_t n = 0)
		: mpData(NULL)
		, mpStart(NULL)
		, mpEnd(NULL)
		, mpDataEnd(NULL)
		, mVersion(0)
	{
		// allocate buffer
		size_t lCapacity = 10 < n ? n: 10;
		mpData = new T[lCapacity];

		// set status
		mpStart = mpEnd = mpData;
		mpDataEnd = mpData + lCapacity;

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

	Consumer<T>* GetReader()
	{
		return new Consumer<T>(&mpData, &mpStart, &mpEnd);
	}

	Consumer<T>* GerWriter()
	{
		return new Consumer<T>(&mpStart, &mpEnd, &mpDataEnd);
	}

	~Buffer()
	{
		delete [] mpData;
	}

	T* mpData;
	T* mpStart;
	T* mpEnd;
	T* mpDataEnd;
	size_t mVersion;
};

template<typename UT, typename T>
class ChainedConsumer: public Consumer<T>
{
public:
	template<typename DT>
	ChainConsumer<T, DT>* Pipe(Adaptor<T, DT>* ipAdaptor)
	{
		return new ChainedConsumer<T, DT>(this, ipAdaptor);
	}

private:
	Consumer<UT>* mpUpstream;
	Adaptor<UT, T>* mpAdaptor;
};

template<class I, class O>
struct Adaptor
{
	virtual size_t operator()(Consumer<I>* ipReader, Consumer<O>* opWriter, size_t iExpectedCount = 1) = 0;
};

template<class I, class O>
struct SimpleAdaptor: public Adaptor<I, O>
{
	size_t operator()(Consumer<I>* ipReader, Consumer<O>* opWriter, size_t iExpectedCount = 1)
	{
		if(ipReader == NULL || opWriter == NULL || iExpectedCount == 0)
		{
			return 0;
		}

		I* lpSrc = NULL;
		size_t lCount = ipReader->Get(&lpSrc, 10000);
		I* lpEnd = lpSrc + lCount;

		for(I* lpLineStart = lpSrc; lpLineStart < lpEnd; )
		{
			I* lpLineEnd = this->InputPause(lpLineStart, lpEnd);
			if(lpLineEnd)
			{
				
			}
		}
	}

	virtual size_t InputPause(const I* ipStart, const I* ipEnd)
	{
		return 0;
	}

	virtual size_t OutputPause(const T* ipStart, const T* ipEnd)
	{
		return 0;
	}
};

int main()
{
	const int SIZE = 10000;
	const int EACH = 1000;

	int v[SIZE];
	for(int i = 0; i < SIZE; i++)
	{
		v[i] = i;
	}

	Buffer<int> lBuffer(SIZE);
	Consumer<int> *lpBufferReader = lBuffer.GetReader();
	Consumer<int> *lpBufferWriter = lBuffer.GerWriter();
	
	cout << lpBufferReader->Size() << " " << lpBufferWriter->Size() << endl;

	// get write buffer
	{
		int *lpWriter = NULL;
		int lCount = lpBufferWriter->Get(&lpWriter, EACH);
		for(int i = 0; i < lCount; i++)
		{
			lpWriter[i] = v[i];
		}
		lpBufferWriter->UnGet(3);
	}

	// get read buffer
	{
		int *lpReader = NULL;
		int lCount = lpBufferReader->Get(&lpReader, EACH);
		for(int i = 0; i < lCount; i++)
		{
			cout << lpReader[i] << " ";
		}
		cout << endl;
	}

	cout << lpBufferReader->Size() << " " << lpBufferWriter->Size() << endl;

	delete lpBufferReader;
	delete lpBufferWriter;

	return 0;
}