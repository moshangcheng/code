#ifndef __BUFFER_H
#define __BUFFER_H

#include <iostream>

/* why not std::basic_stringbuf
   - too complicated
   - does't have APIs for non-copy read/write
   - for C++11, we have std::move
*/


// read and write are dual operations
// read is operation of occupied space
// write is operation of not occupied space


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

#endif