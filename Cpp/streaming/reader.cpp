#include <fstream>
#include <iostream>
#include <cstring>
#include <strstream>


//NO Convert() in general class
template<typename I, typename O> struct Adaptor {};

template<>
struct Adaptor<bool, char>
{
	size_t Convert(bool* i, char* o) const
	{
		o = new char(*i);
		return 1;
	}
};

template<>
struct Adaptor<char, int>
{
	size_t Convert(char* i, int* o) const
	{
		*o = *i;
		return 1;
	}
};

template<>
struct Adaptor<int, double>
{
	size_t Convert(int* i, double* o) const
	{
		*o = *i;
		return 1;
	}
};


template<typename T>
class Reader
{
public:
	//copy, caller is responsible to allocate memory pointed by p
	virtual size_t Read(T* p, size_t n)
	{
		return 0;
	}

	//without copy
	virtual T* Get()
	{
		return NULL;
	}

	virtual ~Reader()
	{
	}
};


template<typename UT, typename T>
class ChainReader: public Reader<T>
{
public:

	ChainReader(Reader<UT>* ipUpstream, const Adaptor<UT, T>& ipAdaptor)
		: mpAdaptor(ipAdaptor)
		, mpUpStream(ipUpstream)
	{}

	~ChainReader()
	{
		delete mpData;
		mpData = NULL;
	}

	template<typename DT>
	ChainReader<T, DT>* Pipe(const Adaptor<T, DT>& ipAdaptor)
	{
		return new ChainReader<T, DT>(this, ipAdaptor);
	}

	//only for 1-1 adaptor
	size_t Read(T* p, size_t n)
	{
		T* lpCurrent = p;
		for(T* lpEnd = p + n; lpCurrent < lpEnd;)
		{
			UT* lpUT = mpUpStream->Get();
			if(!lpUT)
			{
				return lpCurrent - p;
			}
			lpCurrent += mpAdaptor.Convert(lpUT, lpCurrent);
		}
		return n;
	}

	T* Get()
	{
		UT* lpUT = mpUpStream->Get();
		if(lpUT)
		{
			mpData = new T();
			mpAdaptor.Convert(lpUT, mpData);
			return mpData;
		}
		return NULL;
	}

private:
	Reader<UT>* mpUpStream;
	Adaptor<UT, T> mpAdaptor;
	T* mpData;
};


template<typename T>
class ArrayReader: public Reader<T>
{
public:
	ArrayReader(const T* ipArray, size_t n)
		: mpStart(new T[n])
		, mpCurrent(mpStart)
		, mpEnd(mpStart + n)
	{
		for(T *lpDest = mpStart; lpDest < mpEnd;)
		{
			*(lpDest++) = *(ipArray++);
		}
	}

	~ArrayReader()
	{
		delete [] mpStart;
		mpStart = mpCurrent = mpEnd = NULL;
	}

	size_t Read(T* p, size_t n)
	{
		size_t lCount = mpCurrent + n < mpEnd ? n: mpEnd - mpCurrent;
		while(mpCurrent < mpEnd)
		{
			*(p++) = *(mpCurrent++);
		}
		return lCount;
	}

	T* Get()
	{
		return mpCurrent < mpEnd ? mpCurrent++: NULL;
		
	}

	template<typename DT>
	ChainReader<T, DT>* Pipe(const Adaptor<T, DT>& ipAdaptor)
	{
		//TODO: memory leak
		return new ChainReader<T, DT>(this, ipAdaptor);
	}

private:
	T* mpStart;
	T* mpCurrent;
	T* mpEnd;
};


int main()
{
	std::string lpStr = "abcdefghijklmn";
	double lResult[14];

	ArrayReader<char>* lpCharStream = new ArrayReader<char>(lpStr.c_str(), lpStr.length());
	ChainReader<int, double>* lResultStream = lpCharStream->Pipe(Adaptor<char,int>())->Pipe(Adaptor<int,double>());
	
	size_t lCount = lResultStream->Read(lResult, 20);
	for(size_t i = 0; i < lCount; i++)
	{
		std::cout << lResult[i] << std::endl;
	}
	return 0;
}
